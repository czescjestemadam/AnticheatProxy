#include "plugin_message.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

acp::HandleResult acp::packet::configuration::c2s::PluginMessage::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::configuration::c2s::PluginMessage::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x02;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x01;

	return -1;
}
