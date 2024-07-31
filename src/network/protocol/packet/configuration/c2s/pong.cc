#include "pong.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::configuration::c2s::Pong::read(const ProtocolVersion* version)
{
	pongId = buf.readInt();
}

void acp::packet::configuration::c2s::Pong::write(const ProtocolVersion* version)
{
	buf.writeInt(pongId);
}

acp::HandleResult acp::packet::configuration::c2s::Pong::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return acp::HandleResult::FORWARD;
}

int acp::packet::configuration::c2s::Pong::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x05;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x04;

	return -1;
}

int acp::packet::configuration::c2s::Pong::getPongId() const
{
	return pongId;
}

void acp::packet::configuration::c2s::Pong::setPongId(const int pong_id)
{
	pongId = pong_id;
}

std::string acp::packet::configuration::c2s::Pong::toString() const
{
	return std::format("Pong[{}]", pongId);
}
