#include "version_command.hh"

#include "globals.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/minimessage/minimessage_io.hh"

acp::VersionCommand::VersionCommand() : ICommand(nullptr)
{
}

void acp::VersionCommand::execute(ICommandSource* source, const std::vector<std::string>& args)
{
	source->sendMessage(text::ITextIO::minimessage().parse(
			std::format("<{}>AnticheatProxy {} compiled at {}", globals::THEME_COLOR, globals::VERSION, globals::COMPILE_TIME))
	);
}

std::vector<std::string> acp::VersionCommand::complete(ICommandSource* source, const std::vector<std::string>& args)
{
	return {};
}

std::string acp::VersionCommand::getUsage() const
{
	return "version";
}

std::string acp::VersionCommand::getHelpMessage() const
{
	return "Shows version and compilation time";
}


