#pragma once
#include "util/enum_names.hh"

namespace acp
{
	enum class NetworkState
	{
		HANDSHAKE,
		STATUS,
		LOGIN,
		CONFIGURATION,
		PLAY
	};

	template<>
	struct EnumNames<NetworkState>
	{
		static std::string get(NetworkState val)
		{
			switch (val)
			{
				case NetworkState::HANDSHAKE: return "HANDSHAKE";
				case NetworkState::STATUS: return "STATUS";
				case NetworkState::LOGIN: return "LOGIN";
				case NetworkState::CONFIGURATION: return "CONFIGURATION";
				case NetworkState::PLAY: return "PLAY";
				default: return "undefined";
			}
		}
	};
}
