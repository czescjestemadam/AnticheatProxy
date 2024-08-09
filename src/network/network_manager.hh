#pragma once
#include "socket/server_socket.hh"
#include "connection.hh"
#include "socket/epoll_socket.hh"
#include "util/logger/sub_logger.hh"

#include <thread>
#include <memory>

namespace acp
{
	class NetworkManager
	{
		SubLogger logger = SubLogger::fromRoot("NetworkManager");

		std::string destAddress;
		ushort destPort;

		ServerSocket serverSocket;
		std::thread acceptThread;

		std::vector<std::shared_ptr<Connection>> connections;
		std::unordered_map<int, std::weak_ptr<Connection>> connectionByFd;

		EpollSocket epollSocket;
		std::thread epollThread;

	public:
		NetworkManager(const std::string& address, ushort port, const std::string& destAddress, ushort destPort);
		~NetworkManager();

		void start();
		void stop();
		void wait();

		std::weak_ptr<Connection> getByFd(int fd) const;
		std::weak_ptr<Connection> getByUuid(const UUID& uuid) const;
		std::weak_ptr<Connection> getByUsername(const std::string& username) const;
		void addConnection(std::shared_ptr<Connection>&& connection);
		void removeConnection(const std::weak_ptr<Connection>& connection, const std::unique_ptr<text::Component>& reason);

	private:
		void acceptLoop();
		void epollLoop();
	};
}
