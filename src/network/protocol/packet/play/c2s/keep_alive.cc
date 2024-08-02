#include "keep_alive.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::KeepAlive::read(const ProtocolVersion* version)
{
	keepAliveId = buf.readLong();
}

void acp::packet::play::c2s::KeepAlive::write(const ProtocolVersion* version)
{
	buf.writeLong(keepAliveId);
}

acp::HandleResult acp::packet::play::c2s::KeepAlive::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::KeepAlive::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x18;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x15;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x14;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x12;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x11;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x12;
	if (*version >= ProtocolVersion::v1_19)
		return 0x11;
	if (*version >= ProtocolVersion::v1_17)
		return 0x0F;

	return 0x10;
}

long acp::packet::play::c2s::KeepAlive::getKeepAliveId() const
{
	return keepAliveId;
}

void acp::packet::play::c2s::KeepAlive::setKeepAliveId(const long keep_alive_id)
{
	keepAliveId = keep_alive_id;
}

std::string acp::packet::play::c2s::KeepAlive::toString() const
{
	return std::format("KeepAlive[{}]", keepAliveId);
}
