#include "socket_exception.hh"

acp::SocketException::SocketException(const std::string& message, ISocket* socket) : message(message), socket(socket)
{
}

const char* acp::SocketException::what() const noexcept
{
	return message.c_str();
}

acp::ISocket* acp::SocketException::getSocket() const
{
	return socket;
}
