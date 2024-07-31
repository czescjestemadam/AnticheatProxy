#include "i_socket.hh"

#include <format>
#include <unistd.h>
#include <arpa/inet.h>

acp::ISocket::ISocket(int fd, const sockaddr_in& address) : fd(fd), address(address)
{
}

void acp::ISocket::close()
{
	if (fd < 0)
		return;

	shutdown(fd, SHUT_RDWR);
	::close(fd);

	fd = -1;
}

bool acp::ISocket::isValid() const
{
	return fd >= 0;
}

int acp::ISocket::getFd() const
{
	return fd;
}

const sockaddr_in& acp::ISocket::getAddr() const
{
	return address;
}

void acp::ISocket::setAddr(const sockaddr_in& address)
{
	this->address = address;
}

std::string acp::ISocket::getAddrStr() const
{
	return std::format("{}:{}/{}", inet_ntoa(address.sin_addr), ntohs(address.sin_port), fd);
}


bool acp::ISocket::operator==(const ISocket& rhs) const
{
	return fd == rhs.fd;
}

bool acp::ISocket::operator!=(const ISocket& rhs) const
{
	return !(*this == rhs);
}
