#pragma once
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace acp
{
	class RunArgs
	{
		std::vector<std::string> flags;
		std::unordered_map<std::string, std::string> args;

	public:
		RunArgs(int argc, char* argv[]);
		RunArgs(RunArgs&&) = default;

		bool hasFlag(const std::string& name) const;
		std::optional<std::string> getArg(const std::string& name) const;
	};
}
