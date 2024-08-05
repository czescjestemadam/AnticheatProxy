#include "chunk.hh"

acp::game::Chunk::Chunk(const ChunkKey& key) : key(key)
{
}

const acp::game::ChunkKey& acp::game::Chunk::getKey() const
{
	return key;
}

