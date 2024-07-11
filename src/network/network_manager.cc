#include "network_manager.hh"

#include "socket/exception/socket_close_exception.hh"

#include <iostream>
#include <memory>

constexpr int EPOLL_EVENT_COUNT = 32;

acp::NetworkManager::NetworkManager(const std::string& address, ushort port, const std::string& destAddress, ushort destPort)
	: destAddress(destAddress),
	  destPort(destPort),
	  serverSocket(address, port)
{
}

acp::NetworkManager::~NetworkManager()
{
	stop();
}

void acp::NetworkManager::start()
{
	serverSocket.bind();
	serverSocket.listen();

	std::cout << std::format("listening on {}\n", serverSocket.getAddrStr());

	acceptThread = std::thread([this] { this->acceptLoop(); });
	epollThread = std::thread([this] { this->epollLoop(); });
}

void acp::NetworkManager::stop()
{
	serverSocket.close();
	epollSocket.close();

	wait();
}

void acp::NetworkManager::wait()
{
	if (acceptThread.joinable())
		acceptThread.join();

	if (epollThread.joinable())
		epollThread.join();
}

std::weak_ptr<acp::Connection> acp::NetworkManager::getByFd(int fd)
{
	return connectionByFd[fd];
}

void acp::NetworkManager::addConnection(std::shared_ptr<Connection>&& connection)
{
	connectionByFd[connection->getSide(NetworkSide::CLIENT).getFd()] = connection;
	connectionByFd[connection->getSide(NetworkSide::DEST).getFd()] = connection;
	epollSocket.add(connection);
	connections.push_back(std::move(connection));
}

void acp::NetworkManager::removeConnection(const std::weak_ptr<Connection>& connection)
{
	std::shared_ptr<Connection> conn = connection.lock();
	if (!conn)
		return;

	epollSocket.remove(conn);

	const auto& it = std::ranges::find(connections, conn);
	if (it != connections.end())
		connections.erase(it);

	connectionByFd.erase(conn->getSide(NetworkSide::CLIENT).getFd());
	connectionByFd.erase(conn->getSide(NetworkSide::DEST).getFd());

	conn->close();
}


void acp::NetworkManager::acceptLoop()
{
	std::cout << std::format("started accept loop on {}\n", serverSocket.getAddrStr());

	while (serverSocket.isValid())
	{
		try
		{
			PlayerSocket clientSocket = serverSocket.accept();

			std::cout << std::format("{}: accepted {}\n", serverSocket.getAddrStr(), clientSocket.getAddrStr());

			PlayerSocket destSocket = PlayerSocket::create(destAddress, destPort);
			destSocket.connect();

			std::shared_ptr<Connection> connection = std::make_shared<Connection>(std::move(clientSocket), std::move(destSocket));

			std::cout << std::format("{} connected\n", connection->toString());
			this->addConnection(std::move(connection));
		}
		catch (const SocketException& ex)
		{
			std::cerr << std::format("error accepting connection on {}\n", serverSocket.getAddrStr());
			std::cerr << std::format("{}: {}\n", ex.getSocket()->getAddrStr(), ex.what());
		}
	}
}

void acp::NetworkManager::epollLoop()
{
	std::cout << std::format("started epoll wait loop on {}\n", epollSocket.getAddrStr());

	while (epollSocket.isValid())
	{
		for (const epoll_event& event : epollSocket.wait(EPOLL_EVENT_COUNT))
		{
			const int fd = event.data.fd;

			std::weak_ptr<Connection> weakConnection = getByFd(fd);
			if (std::shared_ptr<Connection> connection = weakConnection.lock())
			{
				try
				{
					connection->handleEvent(fd);
				}
				catch (const SocketCloseException& ex)
				{
					std::cout << std::format("connection {} closed\n", connection->toString());
					removeConnection(connection);
				}
				catch (const SocketException& ex)
				{
					std::cerr << std::format("{}: {}\n", ex.getSocket()->getAddrStr(), ex.what());
				}
			}
		}
	}
}
