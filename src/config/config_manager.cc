#include "config_manager.hh"

acp::ConfigManager::ConfigManager(const RunArgs& args)
{
	if (args.hasFlag("default-configs"))
		logger.info("Loading configs skipped (--default-configs)");
	else
		load();
}

void acp::ConfigManager::load()
{
	const std::filesystem::path configsDir = std::filesystem::current_path() / "configs";
	create_directory(configsDir);

	logger.info("Loading configs from {}", configsDir.c_str());

	network.load();
}

void acp::ConfigManager::save()
{
	logger.info("Saving configs");

	network.save();
}

acp::NetworkConfig& acp::ConfigManager::getNetwork()
{
	return network;
}
