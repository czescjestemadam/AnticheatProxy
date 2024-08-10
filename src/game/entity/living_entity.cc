#include "living_entity.hh"

#include <cmath>
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

acp::Vec3d acp::game::LivingEntity::getEyePosition(const ProtocolVersion* version) const
{
	return position + getBoundingBox(version).size().y * 0.85;
}

acp::Vec3d acp::game::LivingEntity::getDirection() const
{
	const double radYaw = yaw * std::numbers::pi / 180;
	const double radPitch = pitch * std::numbers::pi / 180;
	const double xz = std::cos(radPitch);
	return {
		-xz * std::sin(radYaw),
		-std::sin(radPitch),
		xz * std::cos(radYaw)
	};
}

acp::BoundingBoxD acp::game::LivingEntity::getBoundingBox(const ProtocolVersion* version) const
{
	// TODO if (this.getEquippedStack(EquipmentSlot.HEAD).isOf(Items.DRAGON_HEAD)) expand(0.5)
	return Entity::getBoundingBox(version);
}

std::string acp::game::LivingEntity::toString()
{
	return std::format("LivingEntity[headYaw={}, hp={}, {}]", headYaw, health, Entity::toString());
}
