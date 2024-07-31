#include "keep_alive.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::configuration::c2s::KeepAlive::read(const ProtocolVersion* version)
{
	keepAliveId = buf.readLong();
}

void acp::packet::configuration::c2s::KeepAlive::write(const ProtocolVersion* version)
{
	buf.writeLong(keepAliveId);
}

acp::HandleResult acp::packet::configuration::c2s::KeepAlive::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::configuration::c2s::KeepAlive::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x04;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x03;

	return -1;
}

long acp::packet::configuration::c2s::KeepAlive::getKeepAliveId() const
{
	return keepAliveId;
}

void acp::packet::configuration::c2s::KeepAlive::setKeepAliveId(const long keep_alive_id)
{
	keepAliveId = keep_alive_id;
}

std::string acp::packet::configuration::c2s::KeepAlive::toString() const
{
	return std::format("KeepAlive[{}]", keepAliveId);
}
