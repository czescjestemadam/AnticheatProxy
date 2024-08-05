#include "chunk_key.hh"

acp::game::ChunkKey::ChunkKey(long key) : key(key)
{
}

acp::game::ChunkKey::ChunkKey(int x, int z) : x(x), z(z)
{
}

bool acp::game::ChunkKey::operator==(const ChunkKey& rhs) const
{
	return key == rhs.key;
}

bool acp::game::ChunkKey::operator!=(const ChunkKey& rhs) const
{
	return !(*this == rhs);
}


std::size_t std::hash<acp::game::ChunkKey>::operator()(const acp::game::ChunkKey& key) const noexcept
{
	return key.key;
}
