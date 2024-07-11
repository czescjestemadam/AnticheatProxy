#pragma once
#include "socket_exception.hh"

namespace acp
{
	class SocketCloseException : public SocketException
	{
	public:
		explicit SocketCloseException(ISocket* socket);
	};
}
