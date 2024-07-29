#include "update_entity_position_rotation.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::UpdateEntityPositionRotation::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	delta = buf.readVec3s();
	yaw = buf.readAngle();
	pitch = buf.readAngle();
	onGround = buf.readByte();
}

void acp::packet::play::s2c::UpdateEntityPositionRotation::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
	buf.writeVec3s(delta);
	buf.writeAngle(yaw);
	buf.writeAngle(pitch);
	buf.writeByte(onGround);
}

acp::HandleResult acp::packet::play::s2c::UpdateEntityPositionRotation::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::UpdateEntityPositionRotation::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x2F;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x2D;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x2C;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x28;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x29;
	if (*version >= ProtocolVersion::v1_19)
		return 0x27;
	if (*version >= ProtocolVersion::v1_17)
		return 0x2A;

	return 0x28;
}

int acp::packet::play::s2c::UpdateEntityPositionRotation::getEntityId() const
{
	return entityId;
}

void acp::packet::play::s2c::UpdateEntityPositionRotation::setEntityId(const int entity_id)
{
	entityId = entity_id;
}

acp::Vec3s acp::packet::play::s2c::UpdateEntityPositionRotation::getDelta() const
{
	return delta;
}

void acp::packet::play::s2c::UpdateEntityPositionRotation::setDelta(const Vec3s& delta)
{
	this->delta = delta;
}

float acp::packet::play::s2c::UpdateEntityPositionRotation::getYaw() const
{
	return yaw;
}

void acp::packet::play::s2c::UpdateEntityPositionRotation::setYaw(const float yaw)
{
	this->yaw = yaw;
}

float acp::packet::play::s2c::UpdateEntityPositionRotation::getPitch() const
{
	return pitch;
}

void acp::packet::play::s2c::UpdateEntityPositionRotation::setPitch(const float pitch)
{
	this->pitch = pitch;
}

bool acp::packet::play::s2c::UpdateEntityPositionRotation::isOnGround() const
{
	return onGround;
}

void acp::packet::play::s2c::UpdateEntityPositionRotation::setOnGround(const bool on_ground)
{
	onGround = on_ground;
}

std::string acp::packet::play::s2c::UpdateEntityPositionRotation::toString() const
{
	return std::format("UpdateEntityPositionRotation[id={}, delta={} {} {}, rot={} {}, ground={}]",
					   entityId,
					   delta.x, delta.y, delta.z,
					   yaw, pitch,
					   onGround
	);
}
