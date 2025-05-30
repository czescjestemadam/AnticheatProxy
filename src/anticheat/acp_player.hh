#pragma once
#include "check/check_manager.hh"
#include "command/i_command_source.hh"
#include "game/entity/player.hh"
#include "game/item/player_inventory.hh"
#include "game/world/world.hh"
#include "util/raycast/i_raycastable.hh"

#include <memory>

namespace acp
{
	class Connection;

	class AcpPlayer : public game::Player, public IRaycastable, public ICommandSource
	{
		Connection* connection;

		int food = 0;

		bool sprinting = false;

		bool canFly = false;
		bool flying = false;
		float flyingSpeed = 0.05;

		/// from s2c::PlayerAbilities, Creative Mode (Instant Break) - 0x08
		bool instantBreak = false;

		game::World trackedWorld;
		game::PlayerInventory trackedInventory;
		CheckManager checkManager;

	public:
		AcpPlayer();
		AcpPlayer(Connection* connection, int id, const GameProfile& profile, const Identifier& worldName);

		std::vector<std::unique_ptr<RaycastResult>> raycast(const RaycastingOptions& options) const override;

		void sendMessage(std::unique_ptr<text::Component>&& message) override;
		bool hasPermission(const Permission& permission) const override;

		Connection* getConnection() const;

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

		game::PlayerInventory& getTrackedInventory();
		const game::PlayerInventory& getTrackedInventory() const;
		void setTrackedInventory(const game::PlayerInventory& tracked_inventory);

		CheckManager& getCheckManager();
		const CheckManager& getCheckManager() const;

		std::string toString() override;
	};
}
