#include "server_socket.hh"

#include <cstring>
#include <arpa/inet.h>
#include <netinet/tcp.h>

#include "exception/socket_exception.hh"

constexpr int LISTEN_BACKLOG = 32;

acp::ServerSocket::ServerSocket(const std::string& address, ushort port) : ISocket(socket(AF_INET, SOCK_STREAM, 0), {})
{
	if (!isValid())
		throw SocketException(std::string("socket: ") + strerror(errno), this);

	constexpr int optval = 1;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = inet_addr(address.c_str());
	this->address.sin_port = htons(port);
}

void acp::ServerSocket::bind()
{
	if (::bind(fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)))
		throw SocketException(std::string("bind: ") + strerror(errno), this);
}

void acp::ServerSocket::listen()
{
	if (::listen(fd, LISTEN_BACKLOG))
		throw SocketException(std::string("listen: ") + strerror(errno), this);
}

acp::PlayerSocket acp::ServerSocket::accept()
{
	sockaddr_in acceptedAddr{};
	socklen_t len = sizeof(acceptedAddr);

	const int acceptedFd = ::accept(fd, reinterpret_cast<sockaddr*>(&acceptedAddr), &len);
	if (acceptedFd < 0)
		throw SocketException(std::string("accept: ") + strerror(errno), this);

	return { acceptedFd, acceptedAddr, NetworkSide::CLIENT };
}
