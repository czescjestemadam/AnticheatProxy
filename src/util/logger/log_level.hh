#pragma once
#include "util/enum_names.hh"

namespace acp
{
	enum class LogLevel
	{
		DEBUG,
		INFO,
		WARN,
		ERROR,
		CRASH
	};

	template<>
	struct EnumNames<LogLevel>
	{
		static std::string get(LogLevel val)
		{
			switch (val)
			{
				case LogLevel::DEBUG: return "DEBUG";
				case LogLevel::INFO: return "INFO";
				case LogLevel::WARN: return "WARN";
				case LogLevel::ERROR: return "ERROR";
				case LogLevel::CRASH: return "CRASH";
				default: return "unknown";
			}
		}
	};
}
