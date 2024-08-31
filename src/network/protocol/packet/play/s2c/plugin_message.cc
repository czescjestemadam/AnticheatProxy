#include "plugin_message.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

acp::HandleResult acp::packet::play::s2c::PluginMessage::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::PluginMessage::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x19;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x18;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x17;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x15;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x16;
	if (*version >= ProtocolVersion::v1_19)
		return 0x15;
	if (*version >= ProtocolVersion::v1_17)
		return 0x18;

	return 0x17;
}
