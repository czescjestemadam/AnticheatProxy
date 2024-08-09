#pragma once
#include "enum_names.hh"

namespace acp
{
	enum class BlockFace
	{
		BOTTOM,
		TOP,
		NORTH, /// -Z
		SOUTH, /// +Z
		WEST, /// -X
		EAST /// +X
	};

	template<>
	struct EnumNames<BlockFace>
	{
		static std::string get(BlockFace val)
		{
			switch (val)
			{
				case BlockFace::BOTTOM: return "BOTTOM";
				case BlockFace::TOP: return "TOP";
				case BlockFace::NORTH: return "NORTH";
				case BlockFace::SOUTH: return "SOUTH";
				case BlockFace::WEST: return "WEST";
				case BlockFace::EAST: return "EAST";
				default: return "unknown";
			}
		}
	};
}
