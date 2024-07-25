#include "set_player_position_rotation.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::SetPlayerPositionRotation::read(const ProtocolVersion* version)
{
	position = buf.readVec3d();
	yaw = buf.readFloat();
	pitch = buf.readFloat();
	onGround = buf.readByte();
}

void acp::packet::play::c2s::SetPlayerPositionRotation::write(const ProtocolVersion* version)
{
	buf.writeVec3d(position);
	buf.writeFloat(yaw);
	buf.writeFloat(pitch);
	buf.writeByte(onGround);
}

acp::HandleResult acp::packet::play::c2s::SetPlayerPositionRotation::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::c2s::SetPlayerPositionRotation::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x1B;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x18;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x17;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x15;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x14;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x15;
	if (*version >= ProtocolVersion::v1_19)
		return 0x14;
	if (*version >= ProtocolVersion::v1_17)
		return 0x12;

	return 0x13;
}

acp::Vec3d& acp::packet::play::c2s::SetPlayerPositionRotation::getPosition()
{
	return position;
}

void acp::packet::play::c2s::SetPlayerPositionRotation::setPosition(const Vec3d& position)
{
	this->position = position;
}

float acp::packet::play::c2s::SetPlayerPositionRotation::getYaw() const
{
	return yaw;
}

void acp::packet::play::c2s::SetPlayerPositionRotation::setYaw(const float yaw)
{
	this->yaw = yaw;
}

float acp::packet::play::c2s::SetPlayerPositionRotation::getPitch() const
{
	return pitch;
}

void acp::packet::play::c2s::SetPlayerPositionRotation::setPitch(const float pitch)
{
	this->pitch = pitch;
}

bool acp::packet::play::c2s::SetPlayerPositionRotation::isOnGround() const
{
	return onGround;
}

void acp::packet::play::c2s::SetPlayerPositionRotation::setOnGround(bool on_ground)
{
	onGround = on_ground;
}

std::string acp::packet::play::c2s::SetPlayerPositionRotation::toString() const
{
	return std::format("SetPlayerPositionRotation[pos={} {} {}, rot={} {}, ground={}]",
					   position.x, position.y, position.z,
					   yaw, pitch,
					   onGround
	);
}
