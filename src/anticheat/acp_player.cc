#include "acp_player.hh"

#include "network/connection.hh"

#include <complex>
#include <format>

acp::AcpPlayer::AcpPlayer() : AcpPlayer(nullptr, -1, {}, {})
{
}

acp::AcpPlayer::AcpPlayer(Connection* connection, int id, const GameProfile& profile, const Identifier& worldName)
	: Player(id, profile.uuid, {}, 0, 0, true, 0, 20, profile), connection(connection), trackedWorld(worldName), checkManager(connection)
{
}

std::vector<std::unique_ptr<acp::RaycastResult>> acp::AcpPlayer::raycast(const RaycastingOptions& options) const
{
	const Vec3d startPos = getEyePosition(connection->getProtocolVersion());
	const Vec3d direction = getDirection();
	const Vec3d invDirection = 1.0 / direction;
	const Vec3i sign(invDirection.x < 0, invDirection.y < 0, invDirection.z < 0);
	const Vec3d endPos = startPos + direction * options.distance;

	const BoundingBoxD possibleResultsBox(startPos, endPos);

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
				possibleResults.emplace_back(entityBox, std::make_unique<RaycastEntityResult>(id));
		}
	}


	std::vector<std::unique_ptr<RaycastResult>> results;

	for (auto& [box, result] : possibleResults)
	{
		const Vec3d bounds[2] = { box.min, box.max };

		Vec3d tmin{
			(bounds[sign.x].x - startPos.x) * invDirection.x,
			(bounds[sign.y].y - startPos.y) * invDirection.y,
			0
		};

		Vec3d tmax{
			(bounds[1 - sign.x].x - startPos.x) * invDirection.x,
			(bounds[1 - sign.y].y - startPos.y) * invDirection.y,
			0
		};

		if (tmin.x > tmax.y || tmin.y > tmax.x)
			continue;

		if (tmin.y > tmin.x)
			tmin.x = tmin.y;
		if (tmax.y < tmax.x)
			tmax.x = tmax.y;

		tmin.z = (bounds[sign.z].z - startPos.z) * invDirection.z;
		tmax.z = (bounds[1 - sign.z].z - startPos.z) * invDirection.z;

		if (tmin.x > tmax.z || tmin.z > tmax.x)
			continue;

		if (tmin.z > tmin.x)
			tmin.x = tmin.z;
		if (tmax.z < tmax.x)
			tmax.x = tmax.z;

		result->hitDistanceMin = tmin.x;
		result->hitDistanceMax = tmax.x;
		result->hitPositionMin = startPos + direction * tmin.x;
		result->hitPositionMax = startPos + direction * tmax.x;

		results.push_back(std::move(result));

		if (options.stopOnFirstResult)
			break;
	}

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
