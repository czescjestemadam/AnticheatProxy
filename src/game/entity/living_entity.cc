#include "living_entity.hh"

#include <format>

acp::game::LivingEntity::LivingEntity(int id, const UUID& uuid, const EntityType* type, const Vec3d& position, float yaw, float pitch, bool onGround, float headYaw, double health)
	: Entity(id, uuid, type, position, yaw, pitch, onGround), headYaw(headYaw), health(health)
{
}

float acp::game::LivingEntity::getHeadYaw() const
{
	return headYaw;
}

void acp::game::LivingEntity::setHeadYaw(const float head_yaw)
{
	headYaw = head_yaw;
}

double acp::game::LivingEntity::getHealth() const
{
	return health;
}

void acp::game::LivingEntity::setHealth(const double health)
{
	this->health = health;
}

acp::Vec3d acp::game::LivingEntity::getEyePosition() const
{
	// TODO
	return position;
}

std::string acp::game::LivingEntity::toString()
{
	return std::format("LivingEntity[headYaw={}, hp={}, {}]", headYaw, health, Entity::toString());
}
