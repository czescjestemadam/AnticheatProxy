#pragma once
#include "game/entity/player.hh"
#include "game/world/world.hh"

#include <memory>

namespace acp
{
	class AcpPlayer : public game::Player
	{
		int food = 0;

		bool sprinting = false;

		bool canFly = false;
		bool flying = false;
		float flyingSpeed = 0.05;

		/// from s2c::PlayerAbilities, Creative Mode (Instant Break) - 0x08
		bool instantBreak = false;

		game::World trackedWorld;

	public:
		AcpPlayer();
		AcpPlayer(int id, const GameProfile& profile, const Identifier& worldName);

		int getFood() const;
		void setFood(int food);

		bool isSprinting() const;
		void setSprinting(bool sprinting);

		bool isCanFly() const;
		void setCanFly(bool can_fly);

		bool isFlying() const;
		void setFlying(bool flying);

		bool isInstantBreak() const;
		void setInstantBreak(bool instant_break);

		game::World& getTrackedWorld();
		const game::World& getTrackedWorld() const;
		void setTrackedWorld(game::World&& tracked_world);

		std::string toString() override;
	};
}
