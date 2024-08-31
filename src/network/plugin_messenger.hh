#pragma once

#include "network_side.hh"
#include "../util/identifier.hh"
#include "protocol/packet/shared/i_plugin_message.hh"

#include <vector>

namespace acp
{
	class PluginMessenger
	{
		Connection* connection;
		std::vector<Identifier> registeredChannels;

	public:
		explicit PluginMessenger(Connection* connection);

		HandleResult onPluginMessage(NetworkSide to, packet::IPluginMessage* packet);

		void registerChannel(const Identifier& channel);
		void unregisterChannel(const Identifier& channel);

		const std::vector<Identifier>& getRegisteredChannels() const;
	};
}
