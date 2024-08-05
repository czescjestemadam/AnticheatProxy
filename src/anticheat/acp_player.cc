#include "acp_player.hh"

#include <format>

acp::AcpPlayer::AcpPlayer() : AcpPlayer(-1, {}, {})
{
}

acp::AcpPlayer::AcpPlayer(int id, const GameProfile& profile, const Identifier& worldName) : Player(id, profile.uuid, {}, 0, 0, 20, profile), trackedWorld(worldName)
{
}

int acp::AcpPlayer::getFood() const
{
	return food;
}

void acp::AcpPlayer::setFood(const int food)
{
	this->food = food;
}

bool acp::AcpPlayer::isSprinting() const
{
	return sprinting;
}

void acp::AcpPlayer::setSprinting(const bool sprinting)
{
	this->sprinting = sprinting;
}

bool acp::AcpPlayer::isCanFly() const
{
	return canFly;
}

void acp::AcpPlayer::setCanFly(const bool can_fly)
{
	canFly = can_fly;
}

bool acp::AcpPlayer::isFlying() const
{
	return flying;
}

void acp::AcpPlayer::setFlying(const bool flying)
{
	this->flying = flying;
}

bool acp::AcpPlayer::isInstantBreak() const
{
	return instantBreak;
}

void acp::AcpPlayer::setInstantBreak(const bool instant_break)
{
	instantBreak = instant_break;
}

acp::game::World& acp::AcpPlayer::getTrackedWorld()
{
	return trackedWorld;
}

const acp::game::World& acp::AcpPlayer::getTrackedWorld() const
{
	return trackedWorld;
}

void acp::AcpPlayer::setTrackedWorld(game::World&& tracked_world)
{
	trackedWorld = std::move(tracked_world);
}

acp::game::PlayerInventory& acp::AcpPlayer::getTrackedInventory()
{
	return trackedInventory;
}

const acp::game::PlayerInventory& acp::AcpPlayer::getTrackedInventory() const
{
	return trackedInventory;
}

void acp::AcpPlayer::setTrackedInventory(const game::PlayerInventory& tracked_inventory)
{
	trackedInventory = tracked_inventory;
}

std::string acp::AcpPlayer::toString()
{
	return std::format("AcpPlayer[food={}, sprinting={}, flying={}, canFly={}, instantBreak={}, {}]",
					   food,
					   sprinting,
					   flying,
					   canFly,
					   instantBreak,
					   Player::toString()
	);
}
