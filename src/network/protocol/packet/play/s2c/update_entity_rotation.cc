#include "update_entity_rotation.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::UpdateEntityRotation::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	yaw = buf.readAngle();
	pitch = buf.readAngle();
	onGround = buf.readByte();
}

void acp::packet::play::s2c::UpdateEntityRotation::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
	buf.writeAngle(yaw);
	buf.writeAngle(pitch);
	buf.writeByte(onGround);
}

acp::HandleResult acp::packet::play::s2c::UpdateEntityRotation::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::UpdateEntityRotation::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x30;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x2E;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x2D;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x29;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x2A;
	if (*version >= ProtocolVersion::v1_19)
		return 0x28;
	if (*version >= ProtocolVersion::v1_17)
		return 0x2B;

	return 0x29;
}

int acp::packet::play::s2c::UpdateEntityRotation::getEntityId() const
{
	return entityId;
}

void acp::packet::play::s2c::UpdateEntityRotation::setEntityId(const int entity_id)
{
	entityId = entity_id;
}

float acp::packet::play::s2c::UpdateEntityRotation::getYaw() const
{
	return yaw;
}

void acp::packet::play::s2c::UpdateEntityRotation::setYaw(const float yaw)
{
	this->yaw = yaw;
}

float acp::packet::play::s2c::UpdateEntityRotation::getPitch() const
{
	return pitch;
}

void acp::packet::play::s2c::UpdateEntityRotation::setPitch(const float pitch)
{
	this->pitch = pitch;
}

bool acp::packet::play::s2c::UpdateEntityRotation::isOnGround() const
{
	return onGround;
}

void acp::packet::play::s2c::UpdateEntityRotation::setOnGround(const bool on_ground)
{
	onGround = on_ground;
}

std::string acp::packet::play::s2c::UpdateEntityRotation::toString() const
{
	return std::format("UpdateEntityRotation[id={}, rot={} {}, ground={}]", entityId, yaw, pitch, onGround);
}
