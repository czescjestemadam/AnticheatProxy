#pragma once
#include "game/entity/player.hh"

#include <memory>
#include <unordered_map>

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

		std::unordered_map<int, std::unique_ptr<Entity>> trackedEntities;

	public:
		AcpPlayer();
		AcpPlayer(int id, const GameProfile& profile);
		using Player::Player;

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

		std::unordered_map<int, std::unique_ptr<Entity>>& getTrackedEntities();
		const std::unordered_map<int, std::unique_ptr<Entity>>& getTrackedEntities() const;

		std::string toString() override;
	};
}
