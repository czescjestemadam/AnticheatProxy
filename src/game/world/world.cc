#include "world.hh"

acp::game::World::World(const Identifier& dimensionName) : dimensionName(dimensionName)
{
}

const acp::Identifier& acp::game::World::getDimensionName() const
{
	return dimensionName;
}

std::unordered_map<acp::game::ChunkKey, acp::game::Chunk>& acp::game::World::getChunks()
{
	return chunks;
}

const std::unordered_map<acp::game::ChunkKey, acp::game::Chunk>& acp::game::World::getChunks() const
{
	return chunks;
}

std::unordered_map<int, std::unique_ptr<acp::game::Entity>>& acp::game::World::getEntities()
{
	return entities;
}

const std::unordered_map<int, std::unique_ptr<acp::game::Entity>>& acp::game::World::getEntities() const
{
	return entities;
}
