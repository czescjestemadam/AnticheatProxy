#include "reset_chat.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::configuration::s2c::ResetChat::read(const ProtocolVersion* version)
{
}

void acp::packet::configuration::s2c::ResetChat::write(const ProtocolVersion* version)
{
}

acp::HandleResult acp::packet::configuration::s2c::ResetChat::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::configuration::s2c::ResetChat::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x06;

	return -1;
}

std::string acp::packet::configuration::s2c::ResetChat::toString() const
{
	return "ResetChat";
}
