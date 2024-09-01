#include "command_manager.hh"

#include "anticheat/acp_player.hh"
#include "anticheat/command/connection_command.hh"
#include "anticheat/command/help_command.hh"
#include "anticheat/command/reload_command.hh"
#include "anticheat/command/stop_command.hh"
#include "anticheat/command/version_command.hh"
#include "network/connection.hh"
#include "network/protocol/packet/play/s2c/command_suggestions_response.hh"
#include "permission/permission.hh"
#include "util/str_utils.hh"
#include "util/profiler/profiler.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/minimessage/minimessage_io.hh"

acp::CommandManager::CommandManager()
{
	commandByName["connection"] = std::make_unique<ConnectionCommand>();
	commandByName["help"] = std::make_unique<HelpCommand>();
	commandByName["reload"] = std::make_unique<ReloadCommand>();
	commandByName["stop"] = std::make_unique<StopCommand>();
	commandByName["version"] = std::make_unique<VersionCommand>();
}

void acp::CommandManager::executePacket(ICommandSource* source, const std::string& command)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("CommandManager::executePacket()");

	std::vector<std::string> args = StrUtils::split(command);
	args.erase(args.begin()); // on packet erase starting "/acp "

	if (args.empty())
		args.emplace_back("help");

	const std::string name = args.front();
	args.erase(args.begin());

	execute(source, name, args);
}

void acp::CommandManager::completePacket(ICommandSource* source, const std::string& command, int id)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("CommandManager::completePacket()");

	const auto* player = dynamic_cast<AcpPlayer*>(source);
	if (!player)
		return;

	std::vector<std::string> args = StrUtils::split(command);
	args.erase(args.begin()); // on packet erase starting "/acp "

	std::vector<std::string> completions;

	if (args.size() == 1) // completing "/acp _" or "/acp c_"
		completions = getCommandNames();
	else // completing "/acp cmd _"
	{
		const std::string name = args.front();
		args.erase(args.begin());

		completions = complete(source, name, args);
	}

	const int lastArgStart = static_cast<int>(command.rfind(' ')) + 1;
	const int len = static_cast<int>(command.length()) - lastArgStart;

	auto packet = std::make_unique<packet::play::s2c::CommandSuggestionsResponse>();
	packet->setTransactionId(id);
	packet->setStart(lastArgStart);
	packet->setLength(len);

	for (const std::string& completion : StrUtils::retMatches(args.back(), completions))
		packet->getMatches().emplace_back(completion, nullptr);

	player->getConnection()->sendPacket(NetworkSide::CLIENT, std::move(packet));
}

void acp::CommandManager::execute(ICommandSource* source, const std::string& name, const std::vector<std::string>& args)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("CommandManager::execute()");

	if (ICommand* command = getCommand(name))
	{
		if (source->hasPermission(command->getPermission()))
			command->execute(source, args);
		else
			source->sendMessage(text::ITextIO::minimessage().parse(std::format("<red>Missing {} permission", command->getPermission()->getName())));
	}
	else
		source->sendMessage(text::ITextIO::minimessage().parse(std::format("<red>Unknown command {}", name)));
}

std::vector<std::string> acp::CommandManager::complete(ICommandSource* source, const std::string& name, const std::vector<std::string>& args)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("CommandManager::complete()");

	if (ICommand* command = getCommand(name))
	{
		if (source->hasPermission(command->getPermission()))
			return command->complete(source, args);
	}

	return {};
}

acp::ICommand* acp::CommandManager::getCommand(const std::string& name) const
{
	return commandByName.contains(name) ? commandByName.at(name).get() : nullptr;
}

std::vector<std::string> acp::CommandManager::getCommandNames() const
{
	std::vector<std::string> names;

	for (const auto& [name, command] : commandByName)
		names.push_back(name);

	return names;
}
