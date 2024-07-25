#include "finish_configuration.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::configuration::s2c::FinishConfiguration::read(const ProtocolVersion* version)
{
}

void acp::packet::configuration::s2c::FinishConfiguration::write(const ProtocolVersion* version)
{
}

acp::HandleResult acp::packet::configuration::s2c::FinishConfiguration::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::configuration::s2c::FinishConfiguration::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x03;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x02;

	return -1;
}

std::string acp::packet::configuration::s2c::FinishConfiguration::toString() const
{
	return "FinishConfiguration";
}
