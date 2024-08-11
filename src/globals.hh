#pragma once
#include <chrono>

namespace acp::globals
{
	constexpr const char* VERSION = "b0.1";
	constexpr const char* COMPILE_TIME = __DATE__ " " __TIME__;
	const auto STARTED_AT = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
}
