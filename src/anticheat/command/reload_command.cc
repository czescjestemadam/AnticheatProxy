#include "reload_command.hh"

#include "anticheat_proxy.hh"
#include "permission/permission.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/minimessage/minimessage_io.hh"

acp::ReloadCommand::ReloadCommand() : ICommand(&Permission::RELOAD)
{
}

void acp::ReloadCommand::execute(ICommandSource* source, const std::vector<std::string>& args)
{
	AnticheatProxy::get()->getConfigManager().load();
	source->sendMessage(text::ITextIO::minimessage().parse("<yellow>Reloaded configs"));
	AnticheatProxy::get()->getPermissionManager().load();
	source->sendMessage(text::ITextIO::minimessage().parse("<yellow>Reloaded permissions"));
}

std::vector<std::string> acp::ReloadCommand::complete(ICommandSource* source, const std::vector<std::string>& args)
{
	return {};
}

std::string acp::ReloadCommand::getUsage() const
{
	return "reload";
}

std::string acp::ReloadCommand::getHelpMessage() const
{
	return "Reloads configs, permissions";
}
