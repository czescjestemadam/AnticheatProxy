#pragma once
#include "i_socket.hh"
#include "network/connection.hh"

#include <memory>
#include <sys/epoll.h>

namespace acp
{
	class EpollSocket : public ISocket
	{
	public:
		EpollSocket();

		void add(std::weak_ptr<Connection> connection);
		void remove(std::weak_ptr<Connection> connection);

		std::vector<epoll_event> wait(int eventCount);

	private:
		void add(int fd);
		void remove(int fd);
	};
}
