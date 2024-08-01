#include "network_manager.hh"

#include "socket/exception/socket_close_exception.hh"
#include "util/text/translatable_component.hh"

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
	wait();
}

void acp::NetworkManager::start()
{
	logger.info("Starting NetworkManager");

	ProtocolVersion::compileMappings();

	serverSocket.bind();
	serverSocket.listen();

	logger.info("Listening on {}", serverSocket.getAddrStr());

	acceptThread = std::thread([this] { this->acceptLoop(); });
	epollThread = std::thread([this] { this->epollLoop(); });
}

void acp::NetworkManager::stop()
{
	logger.info("Stopping NetworkManager");

	serverSocket.close();
	epollSocket.close();

	const std::unique_ptr<text::Component> closeReason = std::make_unique<text::TranslatableComponent>("disconnect.disconnected");
	for (const std::shared_ptr<Connection>& connection : connections)
		connection->close(closeReason);
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

void acp::NetworkManager::removeConnection(const std::weak_ptr<Connection>& connection, const std::unique_ptr<text::Component>& reason)
{
	const std::shared_ptr<Connection> conn = connection.lock();
	if (!conn)
		return;

	epollSocket.remove(conn);

	const auto& it = std::ranges::find(connections, conn);
	if (it != connections.end())
		connections.erase(it);

	connectionByFd.erase(conn->getSide(NetworkSide::CLIENT).getFd());
	connectionByFd.erase(conn->getSide(NetworkSide::DEST).getFd());

	conn->close(reason);
}


void acp::NetworkManager::acceptLoop()
{
	logger.info("Started accept loop on {}", serverSocket.getAddrStr());

	while (serverSocket.isValid())
	{
		try
		{
			PlayerSocket clientSocket = serverSocket.accept();

			logger.info("Accepted connection from {}", clientSocket.getAddrStr());

			PlayerSocket destSocket = PlayerSocket::create(destAddress, destPort);
			destSocket.connect();

			std::shared_ptr<Connection> connection = std::make_shared<Connection>(std::move(clientSocket), std::move(destSocket));

			logger.info("{} connected", connection->toString());
			this->addConnection(std::move(connection));
		}
		catch (const SocketException& ex)
		{
			if (!serverSocket.isValid())
				break;

			logger.error("Error accepting connection on {}", serverSocket.getAddrStr());
			logger.error("{}: {}", ex.getSocket()->getAddrStr(), ex.what());
		}
	}

	logger.info("Stopped accept loop");
}

void acp::NetworkManager::epollLoop()
{
	logger.info("Started epoll wait loop on {}", epollSocket.getAddrStr());

	while (epollSocket.isValid())
	{
		for (const auto& [events, data] : epollSocket.wait(EPOLL_EVENT_COUNT))
		{
			if (std::shared_ptr<Connection> connection = getByFd(data.fd).lock())
			{
				try
				{
					connection->handleEvent(data.fd);
				}
				catch (const SocketCloseException& ex)
				{
					logger.info("Connection {} closed", connection->toString());
					removeConnection(connection, *ex.getSocket() == serverSocket
													 ? std::make_unique<text::TranslatableComponent>("disconnect.disconnected")
													 : nullptr);
				}
				catch (const SocketException& ex)
				{
					logger.error("handleEvent({}): {}", ex.getSocket()->getAddrStr(), ex.what());
				}
			}
		}
	}

	logger.info("Stopped epoll loop");
}
