#pragma once
#include "util/enum_names.hh"

namespace acp
{
	enum class NetworkSide
	{
		CLIENT,
		DEST
	};

	constexpr NetworkSide getOppositeSide(NetworkSide side)
	{
		return side == NetworkSide::CLIENT ? NetworkSide::DEST : NetworkSide::CLIENT;
	}

	template<>
	struct EnumNames<NetworkSide>
	{
		static std::string get(NetworkSide val)
		{
			switch (val)
			{
				case NetworkSide::CLIENT: return "CLIENT";
				case NetworkSide::DEST: return "DEST";
				default: return "undefined";
			}
		}
	};
}
