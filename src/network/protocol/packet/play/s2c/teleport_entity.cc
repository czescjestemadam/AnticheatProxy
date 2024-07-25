#include "teleport_entity.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::TeleportEntity::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	position = buf.readVec3d();
	yaw = buf.readAngle();
	pitch = buf.readAngle();
	onGround = buf.readByte();
}

void acp::packet::play::s2c::TeleportEntity::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
	buf.writeVec3d(position);
	buf.writeAngle(yaw);
	buf.writeAngle(pitch);
	buf.writeByte(onGround);
}

acp::HandleResult acp::packet::play::s2c::TeleportEntity::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::TeleportEntity::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x70;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x6D;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x6B;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x68;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x64;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x66;
	if (*version >= ProtocolVersion::v1_19)
		return 0x63;
	if (*version >= ProtocolVersion::v1_18)
		return 0x62;
	if (*version >= ProtocolVersion::v1_17)
		return 0x61;

	return 0x56;
}

int acp::packet::play::s2c::TeleportEntity::getEntityId() const
{
	return entityId;
}

void acp::packet::play::s2c::TeleportEntity::setEntityId(const int entity_id)
{
	entityId = entity_id;
}

acp::Vec3d acp::packet::play::s2c::TeleportEntity::getPosition() const
{
	return position;
}

void acp::packet::play::s2c::TeleportEntity::setPosition(const Vec3d& position)
{
	this->position = position;
}

float acp::packet::play::s2c::TeleportEntity::getYaw() const
{
	return yaw;
}

void acp::packet::play::s2c::TeleportEntity::setYaw(const float yaw)
{
	this->yaw = yaw;
}

float acp::packet::play::s2c::TeleportEntity::getPitch() const
{
	return pitch;
}

void acp::packet::play::s2c::TeleportEntity::setPitch(const float pitch)
{
	this->pitch = pitch;
}

bool acp::packet::play::s2c::TeleportEntity::isOnGround() const
{
	return onGround;
}

void acp::packet::play::s2c::TeleportEntity::setOnGround(const bool on_ground)
{
	onGround = on_ground;
}

std::string acp::packet::play::s2c::TeleportEntity::toString() const
{
	return std::format("TeleportEntity[id={}, pos={} {} {}, rot={} {}, ground={}]",
					   entityId,
					   position.x, position.y, position.z,
					   yaw, pitch,
					   onGround
	);
}
