#pragma once
#include <string>
#include <vector>

namespace acp::StrUtils
{
	void replace(std::string& str, const std::string& from, const std::string& to);
	std::string replaced(const std::string& str, const std::string& from, const std::string& to);

	std::vector<std::string> split(std::string str, const std::string& delim = " ");

	std::string join(const std::vector<std::string>& arr, const std::string& delim = ", ");

	std::string toLowerCase(const std::string& str);
	std::string toUpperCase(const std::string& str);

	std::vector<std::string> retMatches(const std::string& arg, const std::vector<std::string>& args);
}
