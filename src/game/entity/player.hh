#pragma once
#include "living_entity.hh"
#include "util/game_profile.hh"

namespace acp::game
{
	class Player : public LivingEntity
	{
	protected:
		GameProfile profile;

	public:
		Player(int id, const UUID& uuid, const Vec3d& position, float yaw, float pitch, double health, const GameProfile& profile);

		const GameProfile& getProfile() const;
		void setProfile(const GameProfile& profile);

		std::string toString() override;
	};
}
