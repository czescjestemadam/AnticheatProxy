#pragma once
#include "../i_socket.hh"

#include <exception>

namespace acp
{
	class SocketException : public std::exception
	{
	protected:
		std::string message;
		ISocket* socket;

	public:
		SocketException(const std::string& message, ISocket* socket);

		const char* what() const noexcept override;

		ISocket* getSocket() const;
	};
}
