#pragma once
#include "i_network_handler.hh"

namespace acp
{
	class LoginHandler : public INetworkHandler
	{
	public:
		using INetworkHandler::INetworkHandler;
	};
}
