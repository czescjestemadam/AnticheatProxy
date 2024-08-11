#pragma once
#include "i_command.hh"

#include <memory>
#include <unordered_map>

namespace acp
{
	class CommandManager
	{
		std::unordered_map<std::string, std::unique_ptr<ICommand>> commandByName;

	public:
		CommandManager();

		void execute(ICommandSource* source, const std::string& name, const std::vector<std::string>& args);
		std::vector<std::string> complete(ICommandSource* source, const std::string& name, const std::vector<std::string>& args);

		std::vector<std::string> getCommandNames() const;
	};
}
