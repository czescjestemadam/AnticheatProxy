#include "epoll_socket.hh"

#include <cstring>
#include <sys/epoll.h>

#include "exception/socket_exception.hh"

acp::EpollSocket::EpollSocket() : ISocket(epoll_create(0xff), {})
{
}

void acp::EpollSocket::add(std::weak_ptr<Connection> connection)
{
	if (std::shared_ptr<Connection> conn = connection.lock())
	{
		add(conn->getSide(NetworkSide::CLIENT).getFd());
		add(conn->getSide(NetworkSide::DEST).getFd());
	}
}

void acp::EpollSocket::remove(std::weak_ptr<Connection> connection)
{
	if (std::shared_ptr<Connection> conn = connection.lock())
	{
		remove(conn->getSide(NetworkSide::CLIENT).getFd());
		remove(conn->getSide(NetworkSide::DEST).getFd());
	}
}

std::vector<epoll_event> acp::EpollSocket::wait(int eventCount)
{
	epoll_event events[eventCount];
	const int ret = epoll_wait(fd, events, eventCount, 1000);
	if (ret < 0)
	{
		const int err = errno;
		if (err == EINTR)
			return {};

		throw SocketException(std::string("epoll_wait: ") + strerror(err), this);
	}

	return { events, events + ret };
}


void acp::EpollSocket::add(int fd)
{
	epoll_event event{};
	event.events = EPOLLIN;
	event.data.fd = fd;

	if (epoll_ctl(this->fd, EPOLL_CTL_ADD, fd, &event) < 0)
		throw SocketException(std::string("epoll_ctl(add): ") + strerror(errno), this);
}

void acp::EpollSocket::remove(int fd)
{
	if (epoll_ctl(this->fd, EPOLL_CTL_DEL, fd, nullptr) < 0)
		throw SocketException(std::string("epoll_ctl(del): ") + strerror(errno), this);
}
