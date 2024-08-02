#include "keep_alive.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::KeepAlive::read(const ProtocolVersion* version)
{
	keepAliveId = buf.readLong();
}

void acp::packet::play::s2c::KeepAlive::write(const ProtocolVersion* version)
{
	buf.writeLong(keepAliveId);
}

acp::HandleResult acp::packet::play::s2c::KeepAlive::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::KeepAlive::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x26;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x24;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x23;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x1F;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x20;
	if (*version >= ProtocolVersion::v1_19)
		return 0x1E;
	if (*version >= ProtocolVersion::v1_17)
		return 0x21;

	return 0x1F;
}

long acp::packet::play::s2c::KeepAlive::getKeepAliveId() const
{
	return keepAliveId;
}

void acp::packet::play::s2c::KeepAlive::setKeepAliveId(const long keep_alive_id)
{
	keepAliveId = keep_alive_id;
}

std::string acp::packet::play::s2c::KeepAlive::toString() const
{
	return std::format("KeepAlive[{}]", keepAliveId);
}
