#include "command_manager.hh"

acp::CommandManager::CommandManager()
{
	// TODO add commands
}

void acp::CommandManager::execute(ICommandSource* source, const std::string& name, const std::vector<std::string>& args)
{
	if (commandByName.contains(name))
	{
		auto& command = commandByName[name];
		if (source->hasPermission(command->getPermission()))
			command->execute(source, args);
	}
}

std::vector<std::string> acp::CommandManager::complete(ICommandSource* source, const std::string& name, const std::vector<std::string>& args)
{
	if (commandByName.contains(name))
	{
		auto& command = commandByName[name];
		if (source->hasPermission(command->getPermission()))
			return command->complete(source, args);
	}

	return {};
}

std::vector<std::string> acp::CommandManager::getCommandNames() const
{
	std::vector<std::string> names;

	for (const auto & [name, command] : commandByName)
		names.push_back(name);

	return names;
}
