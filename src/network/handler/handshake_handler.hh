#pragma once
#include "i_network_handler.hh"
#include "network/protocol/packet/handshake/handshake.hh"

namespace acp
{
	class HandshakeHandler : public INetworkHandler
	{
	public:
		using INetworkHandler::INetworkHandler;

		HandleResult handle(packet::handshake::Handshake* packet);
	};
}
