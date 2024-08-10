#include "player.hh"

#include <format>

acp::game::Player::Player(int id, const UUID& uuid, const Vec3d& position, float yaw, float pitch, bool onGround, float headYaw, double health, const GameProfile& profile)
	: LivingEntity(id, uuid, &EntityType::PLAYER, position, yaw, pitch, onGround, headYaw, health), profile(profile)
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

acp::Vec3d acp::game::Player::getEyePosition(const ProtocolVersion* version) const
{
	// TODO poses: swimming, fall_flying, spin_attack = 0.4

	if (sneaking)
		return position + Vec3d(0, 1.27, 0);

	return position + Vec3d(0, 1.62, 0);
}

acp::BoundingBoxD acp::game::Player::getBoundingBox(const ProtocolVersion* version) const
{
	if (sneaking)
		return BoundingBoxD::fromPos(position, { 0.6, 1.5, 0.6 });
	// TODO other poses

	return LivingEntity::getBoundingBox(version);
}

std::string acp::game::Player::toString()
{
	return std::format("Player[sneaking={}, profile={} {} {}, {}]",
					   sneaking,
					   profile.username, profile.uuid.toString(), profile.properties.size(),
					   LivingEntity::toString()
	);
}
