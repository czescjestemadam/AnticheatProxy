#pragma once
#include "network/network_side.hh"
#include "util/text/component.hh"

namespace acp
{
	class Connection;

	class INetworkHandler
	{
	protected:
		Connection* connection;

	public:
		explicit INetworkHandler(Connection* connection);
		virtual ~INetworkHandler() = default;

		virtual void sendPluginMessage(NetworkSide to, const Identifier& channel, const ByteBuf& data);
		virtual void disconnect(const std::unique_ptr<text::Component>& reason);
	};
}
