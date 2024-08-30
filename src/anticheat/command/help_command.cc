#include "help_command.hh"

#include "anticheat_proxy.hh"
#include "util/str_utils.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/minimessage/minimessage_io.hh"

acp::HelpCommand::HelpCommand() : ICommand(nullptr)
{
}

void acp::HelpCommand::execute(ICommandSource* source, const std::vector<std::string>& args)
{
	const CommandManager& commandManager = AnticheatProxy::get()->getCommandManager();

	if (args.empty())
	{
		source->sendMessage(text::ITextIO::minimessage().parse(
			std::format("<yellow>Available commands: {}", StrUtils::join(commandManager.getCommandNames()))
		));
		return;
	}

	if (const ICommand* command = commandManager.getCommand(args.front()))
		source->sendMessage(text::ITextIO::minimessage().parse(std::format("<red>Usage: {} <yellow>- {}", command->getUsage(), command->getHelpMessage())));
	else
		source->sendMessage(text::ITextIO::minimessage().parse(std::format("<red>Unknown command {}", args.front())));
}

std::vector<std::string> acp::HelpCommand::complete(ICommandSource* source, const std::vector<std::string>& args)
{
	if (args.size() == 1)
		return AnticheatProxy::get()->getCommandManager().getCommandNames();

	return {};
}

std::string acp::HelpCommand::getUsage() const
{
	return "help [command]";
}

std::string acp::HelpCommand::getHelpMessage() const
{
	return "Shows available commands and their help messages";
}
