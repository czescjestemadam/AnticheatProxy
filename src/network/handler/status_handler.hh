#pragma once
#include "i_network_handler.hh"
#include "network/protocol/packet/status/c2s/ping_request.hh"
#include "network/protocol/packet/status/c2s/status_request.hh"
#include "network/protocol/packet/status/s2c/ping_response.hh"
#include "network/protocol/packet/status/s2c/status_response.hh"

namespace acp
{
	class StatusHandler : public INetworkHandler
	{
	public:
		using INetworkHandler::INetworkHandler;

		HandleResult handle(packet::status::c2s::StatusRequest* packet);
		HandleResult handle(packet::status::c2s::PingRequest* packet);

		HandleResult handle(packet::status::s2c::StatusResponse* packet);
		HandleResult handle(packet::status::s2c::PingResponse* packet);
	};
}
