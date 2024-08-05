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

bool acp::game::World::hasChunk(const ChunkKey& key) const
{
	return chunks.contains(key);
}

bool acp::game::World::hasChunk(const Vec3i& pos) const
{
	return hasChunk(ChunkKey(pos.x / 16, pos.z / 16));
}

acp::game::Chunk& acp::game::World::getChunk(const ChunkKey& key)
{
	return chunks.at(key);
}

acp::game::Chunk& acp::game::World::getChunk(const Vec3i& pos)
{
	return getChunk(ChunkKey(pos.x / 16, pos.z / 16));
}

const acp::game::Chunk& acp::game::World::getChunk(const ChunkKey& key) const
{
	return chunks.at(key);
}

const acp::game::Chunk& acp::game::World::getChunk(const Vec3i& pos) const
{
	return getChunk(ChunkKey(pos.x / 16, pos.z / 16));
}

std::unordered_map<int, std::unique_ptr<acp::game::Entity>>& acp::game::World::getEntities()
{
	return entities;
}

const std::unordered_map<int, std::unique_ptr<acp::game::Entity>>& acp::game::World::getEntities() const
{
	return entities;
}

acp::game::Entity* acp::game::World::getEntity(int id) const
{
	return entities.contains(id) ? entities.at(id).get() : nullptr;
}
