#include "set_player_on_ground.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::SetPlayerOnGround::read(const ProtocolVersion* version)
{
	onGround = buf.readByte();
}

void acp::packet::play::c2s::SetPlayerOnGround::write(const ProtocolVersion* version)
{
	buf.writeByte(onGround);
}

acp::HandleResult acp::packet::play::c2s::SetPlayerOnGround::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::SetPlayerOnGround::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x1D;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x1A;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x19;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x17;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x16;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x17;
	if (*version >= ProtocolVersion::v1_19)
		return 0x16;
	if (*version >= ProtocolVersion::v1_17)
		return 0x14;

	return 0x15;
}

bool acp::packet::play::c2s::SetPlayerOnGround::isOnGround() const
{
	return onGround;
}

void acp::packet::play::c2s::SetPlayerOnGround::setOnGround(bool on_ground)
{
	onGround = on_ground;
}

std::string acp::packet::play::c2s::SetPlayerOnGround::toString() const
{
	return std::format("SetPlayerOnGround[{}]", onGround);
}
