#pragma once
#include "chunk.hh"
#include "util/identifier.hh"
#include "game/entity/entity.hh"

#include <unordered_map>
#include <memory>

namespace acp::game
{
	class World
	{
		Identifier dimensionName;
		std::unordered_map<ChunkKey, Chunk> chunks;
		std::unordered_map<int, std::unique_ptr<Entity>> entities;

	public:
		explicit World(const Identifier& dimensionName);

		const Identifier& getDimensionName() const;

		std::unordered_map<ChunkKey, Chunk>& getChunks();
		const std::unordered_map<ChunkKey, Chunk>& getChunks() const;

		bool hasChunk(const ChunkKey& key) const;
		bool hasChunk(const Vec3i& pos) const;
		Chunk& getChunk(const ChunkKey& key);
		Chunk& getChunk(const Vec3i& pos);
		const Chunk& getChunk(const ChunkKey& key) const;
		const Chunk& getChunk(const Vec3i& pos) const;

		std::unordered_map<int, std::unique_ptr<Entity>>& getEntities();
		const std::unordered_map<int, std::unique_ptr<Entity>>& getEntities() const;

		Entity* getEntity(int id) const;
	};
}
