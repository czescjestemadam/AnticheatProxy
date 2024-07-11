#pragma once
#include "i_network_handler.hh"

namespace acp
{
	class HandshakeHandler : public INetworkHandler
	{
	public:
		using INetworkHandler::INetworkHandler;
	};
}
