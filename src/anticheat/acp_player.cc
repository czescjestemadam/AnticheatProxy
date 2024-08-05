#include "acp_player.hh"

#include <format>

acp::AcpPlayer::AcpPlayer() : AcpPlayer(-1, {})
{
}

acp::AcpPlayer::AcpPlayer(int id, const GameProfile& profile) : AcpPlayer(id, profile.uuid, {}, 0, 0, 20, profile)
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

std::unordered_map<int, std::unique_ptr<acp::game::Entity>>& acp::AcpPlayer::getTrackedEntities()
{
	return trackedEntities;
}

const std::unordered_map<int, std::unique_ptr<acp::game::Entity>>& acp::AcpPlayer::getTrackedEntities() const
{
	return trackedEntities;
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
