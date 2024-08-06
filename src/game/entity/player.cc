#include "player.hh"

#include <format>

acp::game::Player::Player(int id, const UUID& uuid, const Vec3d& position, float yaw, float pitch, bool onGround, double health, const GameProfile& profile)
	: LivingEntity(id, uuid, &EntityType::PLAYER, position, yaw, pitch, onGround, health), profile(profile)
{
}

const acp::GameProfile& acp::game::Player::getProfile() const
{
	return profile;
}

void acp::game::Player::setProfile(const GameProfile& profile)
{
	this->profile = profile;
}

bool acp::game::Player::isSneaking() const
{
	return sneaking;
}

void acp::game::Player::setSneaking(const bool sneaking)
{
	this->sneaking = sneaking;
}

std::string acp::game::Player::toString()
{
	return std::format("Player[sneaking={}, profile={} {} {}, {}]",
					   sneaking,
					   profile.username, profile.uuid.toString(), profile.properties.size(),
					   LivingEntity::toString()
	);
}
