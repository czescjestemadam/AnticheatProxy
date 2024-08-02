#include "living_entity.hh"

#include <format>

acp::game::LivingEntity::LivingEntity(int id, const UUID& uuid, const Vec3d& position, float yaw, float pitch, double health)
	: Entity(id, uuid, position, yaw, pitch), health(health)
{
}

double acp::game::LivingEntity::getHealth() const
{
	return health;
}

void acp::game::LivingEntity::setHealth(const double health)
{
	this->health = health;
}

std::string acp::game::LivingEntity::toString()
{
	return std::format("LivingEntity[hp={}, {}]", health, Entity::toString());
}
