#include "acp_player.hh"

#include "network/connection.hh"

#include <complex>
#include <format>

acp::AcpPlayer::AcpPlayer() : AcpPlayer(nullptr, -1, {}, {})
{
}

acp::AcpPlayer::AcpPlayer(Connection* connection, int id, const GameProfile& profile, const Identifier& worldName)
	: Player(id, profile.uuid, {}, 0, 0, true, 0, 20, profile), connection(connection), trackedWorld(worldName), checkManager(this)
{
}

std::vector<std::unique_ptr<acp::RaycastResult>> acp::AcpPlayer::raycast(const RaycastingOptions& options) const
{
	SubLogger logger = connection->getLogger().getSubLogger("Raycasting");

	const Vec3d startPos = getEyePosition(connection->getProtocolVersion());
	const Vec3d endPos = startPos + getDirection() * options.distance;

	const BoundingBoxD possibleResultsBox(startPos, endPos);
	logger.debug("results box: {}", possibleResultsBox.toString());

	std::vector<std::pair<BoundingBoxD, std::unique_ptr<RaycastResult>>> possibleResults;
	if (options.blocks)
	{
		// TODO
	}

	if (options.entities)
	{
		for (const auto& [id, entity] : trackedWorld.getEntities())
		{
			const BoundingBoxD entityBox = entity->getBoundingBox(connection->getProtocolVersion());
			if (entityBox.contains(startPos) || possibleResultsBox.intersects(entityBox))
			{
				logger.debug("entity box: {}", entityBox.toString());
				possibleResults.emplace_back(entityBox, std::make_unique<RaycastEntityResult>(Vec3d{}, id));
			}
		}
	}


	std::vector<std::unique_ptr<RaycastResult>> results;


	return results;
}

acp::Connection* acp::AcpPlayer::getConnection() const
{
	return connection;
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

acp::CheckManager& acp::AcpPlayer::getCheckManager()
{
	return checkManager;
}

const acp::CheckManager& acp::AcpPlayer::getCheckManager() const
{
	return checkManager;
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
