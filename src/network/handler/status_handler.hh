#pragma once
#include "i_network_handler.hh"

namespace acp
{
	class StatusHandler : public INetworkHandler
	{
	public:
		using INetworkHandler::INetworkHandler;
	};
}
