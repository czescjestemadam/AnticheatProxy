#include "acknowledge_configuration.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::AcknowledgeConfiguration::read(const ProtocolVersion* version)
{
}

void acp::packet::play::c2s::AcknowledgeConfiguration::write(const ProtocolVersion* version)
{
}

acp::HandleResult acp::packet::play::c2s::AcknowledgeConfiguration::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::AcknowledgeConfiguration::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x0C;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x0B;

	return -1;
}

std::string acp::packet::play::c2s::AcknowledgeConfiguration::toString() const
{
	return "AcknowledgeConfiguration";
}
