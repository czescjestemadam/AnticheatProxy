#include "acknowledge_finish_configuration.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::configuration::c2s::AcknowledgeFinishConfiguration::read(const ProtocolVersion* version)
{
}

void acp::packet::configuration::c2s::AcknowledgeFinishConfiguration::write(const ProtocolVersion* version)
{
}

bool acp::packet::configuration::c2s::AcknowledgeFinishConfiguration::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return false;
}

int acp::packet::configuration::c2s::AcknowledgeFinishConfiguration::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x03;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x02;

	return -1;
}

std::string acp::packet::configuration::c2s::AcknowledgeFinishConfiguration::toString() const
{
	return "AcknowledgeFinishConfiguration";
}
