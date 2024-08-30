#include "stop_command.hh"

#include "anticheat_proxy.hh"
#include "permission/permission.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/minimessage/minimessage_io.hh"

acp::StopCommand::StopCommand() : ICommand(&Permission::STOP)
{
}

void acp::StopCommand::execute(ICommandSource* source, const std::vector<std::string>& args)
{
	source->sendMessage(text::ITextIO::minimessage().parse("<red><bold>Stopping"));
	AnticheatProxy::get()->stop();
}

std::vector<std::string> acp::StopCommand::complete(ICommandSource* source, const std::vector<std::string>& args)
{
	return {};
}

std::string acp::StopCommand::getUsage() const
{
	return "stop";
}

std::string acp::StopCommand::getHelpMessage() const
{
	return "Stops the proxy";
}
