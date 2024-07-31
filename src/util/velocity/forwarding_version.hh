#pragma once
#include "util/enum_names.hh"

namespace acp
{
	namespace velocity
	{
		enum class ForwardingVersion
		{
			UNKNOWN,
			MODERN_DEFAULT,
			MODERN_WITH_KEY,
			MODERN_WITH_KEY_V2,
			MODER_LAZY_SESSION,
		};
	}

	template<>
	struct EnumNames<velocity::ForwardingVersion>
	{
		static std::string get(velocity::ForwardingVersion val)
		{
			switch (val)
			{
				case velocity::ForwardingVersion::MODERN_DEFAULT: return "MODERN_DEFAULT";
				case velocity::ForwardingVersion::MODERN_WITH_KEY: return "MODERN_WITH_KEY";
				case velocity::ForwardingVersion::MODERN_WITH_KEY_V2: return "MODERN_WITH_KEY_V2";
				case velocity::ForwardingVersion::MODER_LAZY_SESSION: return "MODERN_LAZY_SESSION";

				default:
				case velocity::ForwardingVersion::UNKNOWN: return "unknown";
			}
		}
	};
}
