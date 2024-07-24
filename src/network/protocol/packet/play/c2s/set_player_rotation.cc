#include "set_player_rotation.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::SetPlayerRotation::read(const ProtocolVersion* version)
{
	yaw = buf.readFloat();
	pitch = buf.readFloat();
	onGround = buf.readByte();
}

void acp::packet::play::c2s::SetPlayerRotation::write(const ProtocolVersion* version)
{
	buf.writeFloat(yaw);
	buf.writeFloat(pitch);
	buf.writeByte(onGround);
}

bool acp::packet::play::c2s::SetPlayerRotation::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::c2s::SetPlayerRotation::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x1C;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x19;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x18;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x16;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x15;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x16;
	if (*version >= ProtocolVersion::v1_19)
		return 0x15;
	if (*version >= ProtocolVersion::v1_17)
		return 0x13;

	return 0x14;
}

float acp::packet::play::c2s::SetPlayerRotation::getYaw() const
{
	return yaw;
}

void acp::packet::play::c2s::SetPlayerRotation::setYaw(float yaw)
{
	this->yaw = yaw;
}

float acp::packet::play::c2s::SetPlayerRotation::getPitch() const
{
	return pitch;
}

void acp::packet::play::c2s::SetPlayerRotation::setPitch(float pitch)
{
	this->pitch = pitch;
}

bool acp::packet::play::c2s::SetPlayerRotation::isOnGround() const
{
	return onGround;
}

void acp::packet::play::c2s::SetPlayerRotation::setOnGround(bool on_ground)
{
	onGround = on_ground;
}

std::string acp::packet::play::c2s::SetPlayerRotation::toString() const
{
	return std::format("SetPlayerRotation[rot={} {}, ground={}]", yaw, pitch, onGround);
}
