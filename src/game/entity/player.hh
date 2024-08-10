#pragma once
#include "living_entity.hh"
#include "util/game_profile.hh"

namespace acp::game
{
	class Player : public LivingEntity
	{
	protected:
		GameProfile profile;

		bool sneaking = false;

	public:
		Player(int id, const UUID& uuid, const Vec3d& position, float yaw, float pitch, bool onGround, float headYaw, double health, const GameProfile& profile);

		const GameProfile& getProfile() const;
		void setProfile(const GameProfile& profile);

		bool isSneaking() const;
		void setSneaking(bool sneaking);

		Vec3d getEyePosition(const ProtocolVersion* version) const override;
		BoundingBoxD getBoundingBox(const ProtocolVersion* version) const override;

		std::string toString() override;
	};
}
