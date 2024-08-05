#pragma once
#include "chunk_key.hh"

namespace acp::game
{
	class Chunk
	{
		ChunkKey key;
		// TODO blocks, block entities

	public:
		explicit Chunk(const ChunkKey& key);

		const ChunkKey& getKey() const;
	};
}


