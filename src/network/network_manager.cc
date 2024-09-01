#include "network_manager.hh"

#include "anticheat_proxy.hh"
#include "protocol/packet/play/s2c/keep_alive.hh"
#include "socket/exception/socket_close_exception.hh"
#include "util/profiler/profiler.hh"
#include "util/text/translatable_component.hh"

#include <memory>
#include <random>

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
	ProfilerStackGuard guard = Profiler::get().pushGuard("NetworkManager::start()");

	logger.info("Starting NetworkManager");

	ProtocolVersion::compileMappings(logger.getSubLogger("ProtocolVersion"));

	serverSocket.bind();
	serverSocket.listen();

	logger.info("Listening on {}", serverSocket.getAddrStr());

	acceptThread = std::thread([this] { this->acceptLoop(); });
	epollThread = std::thread([this] { this->epollLoop(); });
	keepAliveSenderThread = std::thread([this] { this->keepAliveSenderLoop(); });
}

void acp::NetworkManager::stop()
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("NetworkManager::stop()");

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

	if (keepAliveSenderThread.joinable())
		keepAliveSenderThread.join();
}

std::weak_ptr<acp::Connection> acp::NetworkManager::getByFd(int fd) const
{
	if (connectionByFd.contains(fd))
		return connectionByFd.at(fd);
	return {};
}

std::weak_ptr<acp::Connection> acp::NetworkManager::getByUuid(const UUID& uuid) const
{
	for (const std::shared_ptr<Connection>& connection : connections)
		if (connection->getGameProfile().uuid == uuid)
			return connection;

	return {};
}

std::weak_ptr<acp::Connection> acp::NetworkManager::getByUsername(const std::string& username) const
{
	for (const std::shared_ptr<Connection>& connection : connections)
		if (connection->getGameProfile().username == username)
			return connection;

	return {};
}

std::vector<std::shared_ptr<acp::Connection>>& acp::NetworkManager::getConnections()
{
	return connections;
}

const std::vector<std::shared_ptr<acp::Connection>>& acp::NetworkManager::getConnections() const
{
	return connections;
}

void acp::NetworkManager::addConnection(std::shared_ptr<Connection>&& connection)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("NetworkManager::addConnection()");

	connectionByFd[connection->getSide(NetworkSide::CLIENT).getFd()] = connection;
	connectionByFd[connection->getSide(NetworkSide::DEST).getFd()] = connection;
	epollSocket.add(connection);
	connections.push_back(std::move(connection));
}

void acp::NetworkManager::removeConnection(const std::weak_ptr<Connection>& connection, const std::unique_ptr<text::Component>& reason)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("NetworkManager::removeConnection()");

	const std::shared_ptr<Connection> conn = connection.lock();
	if (!conn)
		return;

	epollSocket.remove(conn);

	const auto& it = std::ranges::find(connections, conn);
	if (it != connections.end())
		connections.erase(it);

	connectionByFd.erase(conn->getSide(NetworkSide::CLIENT).getFd());
	connectionByFd.erase(conn->getSide(NetworkSide::DEST).getFd());

	try
	{
		conn->close(reason);
	}
	catch (const SocketException& ex)
	{
	}
}


void acp::NetworkManager::acceptLoop()
{
	logger.info("Started accept loop on {}", serverSocket.getAddrStr());

	while (serverSocket.isValid())
	{
		try
		{
			PlayerSocket clientSocket = serverSocket.accept();

			ProfilerStackGuard guard = Profiler::get().pushGuard("NetworkManager::acceptLoop() try{}");

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
				ProfilerStackGuard guard = Profiler::get().pushGuard("NetworkManager::epollLoop() if (conn) {}");

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

void acp::NetworkManager::keepAliveSenderLoop()
{
	logger.info("Started KeepAlive sender loop");

	std::random_device rd;
	std::mt19937_64 rng(rd());
	std::uniform_int_distribution<long> dist;

	while (epollSocket.isValid())
	{
		for (std::shared_ptr<Connection>& connection : connections)
		{
			if (connection->getState() != NetworkState::PLAY)
				continue;

			const long id = 0 - dist(rng);
			auto packet = std::make_unique<packet::play::s2c::KeepAlive>();
			packet->setKeepAliveId(id);

			connection->getPingTracker().onSend(id);
			connection->sendPacket(NetworkSide::CLIENT, std::move(packet));
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(AnticheatProxy::get()->getConfigManager().getNetwork().keepAliveSenderIntervalMs));
	}

	logger.info("Stopped KeepAlive sender loop");
}
