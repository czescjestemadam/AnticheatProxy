#pragma once

namespace acp::globals
{
	constexpr const char* VERSION = "b0.1";
	constexpr const char* COMPILE_TIME = __DATE__ " " __TIME__;
	const std::chrono::system_clock::time_point STARTED_AT = std::chrono::system_clock::now();
}
