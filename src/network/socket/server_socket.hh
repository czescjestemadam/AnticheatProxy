#pragma once
#include "i_socket.hh"
#include "player_socket.hh"

namespace acp
{
	class ServerSocket : public ISocket
	{
	public:
		ServerSocket(const std::string& address, ushort port);
		ServerSocket(ServerSocket&&) = default;

		void bind();
		void listen();

		PlayerSocket accept();
	};
}


