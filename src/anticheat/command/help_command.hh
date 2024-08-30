#pragma once
#include "command/i_command.hh"

namespace acp
{
	class HelpCommand : public ICommand
	{
	public:
		HelpCommand();

		void execute(ICommandSource* source, const std::vector<std::string>& args) override;
		std::vector<std::string> complete(ICommandSource* source, const std::vector<std::string>& args) override;

		std::string getUsage() const override;
		std::string getHelpMessage() const override;
	};
}
