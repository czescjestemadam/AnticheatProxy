#include "entity.hh"

#include <format>

acp::game::Entity::Entity(int id, const UUID& uuid, const EntityType* type, const Vec3d& position, float yaw, float pitch, bool onGround)
	: id(id), uuid(uuid), type(type), position(position), yaw(yaw), pitch(pitch), onGround(onGround)
{
}

int acp::game::Entity::getId() const
{
	return id;
}

const acp::UUID& acp::game::Entity::getUuid() const
{
	return uuid;
}

void acp::game::Entity::setUuid(const UUID& uuid)
{
	this->uuid = uuid;
}

const acp::game::EntityType* acp::game::Entity::getType() const
{
	return type;
}

acp::Vec3d& acp::game::Entity::getPosition()
{
	return position;
}

const acp::Vec3d& acp::game::Entity::getPosition() const
{
	return position;
}

void acp::game::Entity::setPosition(const Vec3d& position)
{
	this->position = position;
}

float acp::game::Entity::getYaw() const
{
	return yaw;
}

void acp::game::Entity::setYaw(const float yaw)
{
	this->yaw = yaw;
}

float acp::game::Entity::getPitch() const
{
	return pitch;
}

void acp::game::Entity::setPitch(const float pitch)
{
	this->pitch = pitch;
}

bool acp::game::Entity::isOnGround() const
{
	return onGround;
}

void acp::game::Entity::setOnGround(const bool on_ground)
{
	onGround = on_ground;
}

std::string acp::game::Entity::toString()
{
	return std::format("Entity[id={}, uuid={}, type={}, pos={} {} {}, rot={} {}, ground={}]",
					   id,
					   uuid.toString(),
					   type->getName(),
					   position.x, position.y, position.z,
					   yaw, pitch,
					   onGround
	);
}
