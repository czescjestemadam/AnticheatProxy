#pragma once
#include <cstddef>

namespace acp::game
{
	struct ChunkKey
	{
		union
		{
			long key;

			struct
			{
				int x, z;
			};
		};

		explicit ChunkKey(long key);
		ChunkKey(int x, int z);

		bool operator==(const ChunkKey& rhs) const;
		bool operator!=(const ChunkKey& rhs) const;
	};
}

namespace std
{
	template<class Key>
	struct hash;

	template<>
	struct hash<acp::game::ChunkKey>
	{
		std::size_t operator()(const acp::game::ChunkKey& key) const noexcept;
	};
}

