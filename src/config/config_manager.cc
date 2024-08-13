#include "config_manager.hh"

#include "util/profiler/profiler.hh"

acp::ConfigManager::ConfigManager(const RunArgs& args)
{
	if (args.hasFlag("default-configs"))
		logger.info("Loading configs skipped (--default-configs)");
	else
		load();
}

void acp::ConfigManager::load()
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("ConfigManager::load()");

	const std::filesystem::path configsDir = std::filesystem::current_path() / "configs";
	create_directory(configsDir);

	logger.info("Loading configs from {}", configsDir.c_str());

	network.load();
	alert.load();
}

void acp::ConfigManager::save()
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("ConfigManager::save()");

	logger.info("Saving configs");

	network.save();
	alert.save();
}

acp::NetworkConfig& acp::ConfigManager::getNetwork()
{
	return network;
}

acp::AlertConfig& acp::ConfigManager::getAlert()
{
	return alert;
}
