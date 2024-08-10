#pragma once
#include "enum_names.hh"

namespace acp
{
	enum class BoxFace
	{
		BOTTOM,
		TOP,
		NORTH, /// -Z
		SOUTH, /// +Z
		WEST, /// -X
		EAST /// +X
	};

	template<>
	struct EnumNames<BoxFace>
	{
		static std::string get(BoxFace val)
		{
			switch (val)
			{
				case BoxFace::BOTTOM: return "BOTTOM";
				case BoxFace::TOP: return "TOP";
				case BoxFace::NORTH: return "NORTH";
				case BoxFace::SOUTH: return "SOUTH";
				case BoxFace::WEST: return "WEST";
				case BoxFace::EAST: return "EAST";
				default: return "unknown";
			}
		}
	};
}
