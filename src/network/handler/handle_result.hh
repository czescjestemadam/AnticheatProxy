#pragma once
#include "util/enum_names.hh"

namespace acp
{
	enum class HandleResult
	{
		FORWARD,
		REWRITE,
		CANCEL
	};

	template<>
	struct EnumNames<HandleResult>
	{
		static std::string get(HandleResult val)
		{
			switch (val)
			{
				case HandleResult::FORWARD: return "FORWARD";
				case HandleResult::REWRITE: return "REWRITE";
				case HandleResult::CANCEL: return "CANCEL";
				default: return "unknown";
			}
		}
	};
}
