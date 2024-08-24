#pragma once
#include <format>
#include <string>

namespace acp::StrUtils
{
	void replace(std::string& str, const std::string& from, const std::string& to);
	std::string replaced(const std::string& str, const std::string& from, const std::string& to);
}
