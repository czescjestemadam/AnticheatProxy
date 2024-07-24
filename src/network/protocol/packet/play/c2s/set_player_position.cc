#include "set_player_position.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::SetPlayerPosition::read(const ProtocolVersion* version)
{
	position = buf.readVec3d();
	onGround = buf.readByte();
}

void acp::packet::play::c2s::SetPlayerPosition::write(const ProtocolVersion* version)
{
	buf.writeVec3d(position);
	buf.writeByte(onGround);
}

bool acp::packet::play::c2s::SetPlayerPosition::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::c2s::SetPlayerPosition::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x1A;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x17;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x16;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x14;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x13;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x14;
	if (*version >= ProtocolVersion::v1_19)
		return 0x13;
	if (*version >= ProtocolVersion::v1_17)
		return 0x11;

	return 0x12;
}

acp::Vec3d& acp::packet::play::c2s::SetPlayerPosition::getPosition()
{
	return position;
}

void acp::packet::play::c2s::SetPlayerPosition::setPosition(const Vec3d& position)
{
	this->position = position;
}

bool acp::packet::play::c2s::SetPlayerPosition::isOnGround() const
{
	return onGround;
}

void acp::packet::play::c2s::SetPlayerPosition::setOnGround(const bool on_ground)
{
	onGround = on_ground;
}

std::string acp::packet::play::c2s::SetPlayerPosition::toString() const
{
	return std::format("SetPlayerPosition[pos={} {} {}, ground={}]", position.x, position.y, position.z, onGround);
}
