#include "socket_close_exception.hh"

acp::SocketCloseException::SocketCloseException(ISocket* socket) : SocketException("closed", socket)
{
}
