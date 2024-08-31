#pragma once
#include "network/protocol/packet/shared/i_plugin_message.hh"

namespace acp::packet::play::s2c
{
	class PluginMessage : public IPluginMessage
	{
	public:
		using IPluginMessage::IPluginMessage;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;
	};
}
