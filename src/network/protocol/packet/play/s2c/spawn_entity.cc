#include "spawn_entity.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::SpawnEntity::read(const ProtocolVersion* version)
{
	entityId = buf.readVarint();
	entityUuid = buf.readUuid();
	type = buf.readVarint();
	position = buf.readVec3d();
	pitch = buf.readAngle();
	yaw = buf.readAngle();
	if (*version >= ProtocolVersion::v1_19)
		headYaw = buf.readAngle();
	data = buf.readVarint();
	velocity = buf.readVec3s();
}

void acp::packet::play::s2c::SpawnEntity::write(const ProtocolVersion* version)
{
	buf.writeVarint(entityId);
	buf.writeUuid(entityUuid);
	buf.writeVarint(type);
	buf.writeVec3d(position);
	buf.writeAngle(pitch);
	buf.writeAngle(yaw);
	if (*version >= ProtocolVersion::v1_19)
		buf.writeAngle(headYaw.value());
	buf.writeVarint(data);
	buf.writeVec3s(velocity);
}

acp::HandleResult acp::packet::play::s2c::SpawnEntity::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::SpawnEntity::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x01;

	return 0x00;
}

int acp::packet::play::s2c::SpawnEntity::getEntityId() const
{
	return entityId;
}

void acp::packet::play::s2c::SpawnEntity::setEntityId(const int entity_id)
{
	entityId = entity_id;
}

acp::UUID acp::packet::play::s2c::SpawnEntity::getEntityUuid() const
{
	return entityUuid;
}

void acp::packet::play::s2c::SpawnEntity::setEntityUuid(const UUID& entity_uuid)
{
	entityUuid = entity_uuid;
}

int acp::packet::play::s2c::SpawnEntity::getType() const
{
	return type;
}

void acp::packet::play::s2c::SpawnEntity::setType(const int type)
{
	this->type = type;
}

acp::Vec3d acp::packet::play::s2c::SpawnEntity::getPosition() const
{
	return position;
}

void acp::packet::play::s2c::SpawnEntity::setPosition(const Vec3d& position)
{
	this->position = position;
}

float acp::packet::play::s2c::SpawnEntity::getPitch() const
{
	return pitch;
}

void acp::packet::play::s2c::SpawnEntity::setPitch(const float pitch)
{
	this->pitch = pitch;
}

float acp::packet::play::s2c::SpawnEntity::getYaw() const
{
	return yaw;
}

void acp::packet::play::s2c::SpawnEntity::setYaw(const float yaw)
{
	this->yaw = yaw;
}

const std::optional<float>& acp::packet::play::s2c::SpawnEntity::getHeadYaw() const
{
	return headYaw;
}

void acp::packet::play::s2c::SpawnEntity::setHeadYaw(const std::optional<float>& head_yaw)
{
	headYaw = head_yaw;
}

int acp::packet::play::s2c::SpawnEntity::getData() const
{
	return data;
}

void acp::packet::play::s2c::SpawnEntity::setData(const int data)
{
	this->data = data;
}

acp::Vec3s acp::packet::play::s2c::SpawnEntity::getVelocity() const
{
	return velocity;
}

void acp::packet::play::s2c::SpawnEntity::setVelocity(const Vec3s& velocity)
{
	this->velocity = velocity;
}

std::string acp::packet::play::s2c::SpawnEntity::toString() const
{
	return std::format("SpawnEntity[id={}, uuid={}, type={}, pos={} {} {}, rot={} {}, headYaw={}, data={}, vel={} {} {}]",
					   entityId,
					   entityUuid.toString(),
					   type,
					   position.x, position.y, position.z,
					   yaw, pitch,
					   headYaw.value_or(-1),
					   data,
					   velocity.x, velocity.y, velocity.z
	);
}
