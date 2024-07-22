#include "teleport_entity.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::TeleportEntity::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	x = buf.readDouble();
	y = buf.readDouble();
	z = buf.readDouble();
	yaw = buf.readAngle();
	pitch = buf.readAngle();
	onGround = buf.readByte();
}

void acp::packet::play::s2c::TeleportEntity::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
	buf.writeDouble(x);
	buf.writeDouble(y);
	buf.writeDouble(z);
	buf.writeAngle(yaw);
	buf.writeAngle(pitch);
	buf.writeByte(onGround);
}

bool acp::packet::play::s2c::TeleportEntity::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
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

double acp::packet::play::s2c::TeleportEntity::getX() const
{
	return x;
}

void acp::packet::play::s2c::TeleportEntity::setX(const double x)
{
	this->x = x;
}

double acp::packet::play::s2c::TeleportEntity::getY() const
{
	return y;
}

void acp::packet::play::s2c::TeleportEntity::setY(const double y)
{
	this->y = y;
}

double acp::packet::play::s2c::TeleportEntity::getZ() const
{
	return z;
}

void acp::packet::play::s2c::TeleportEntity::setZ(const double z)
{
	this->z = z;
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
					   x, y, z,
					   yaw, pitch,
					   onGround
	);
}
