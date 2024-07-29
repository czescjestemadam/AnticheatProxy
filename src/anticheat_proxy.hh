#pragma once
#include "run_args.hh"
#include "config/config_manager.hh"
#include "network/network_manager.hh"
#include "util/logger/logger.hh"

namespace acp
{
	class AnticheatProxy
	{
		RunArgs args;
		Logger logger;
		ConfigManager configManager;
		NetworkManager networkManager;

	public:
		explicit AnticheatProxy(RunArgs&& args);

		void start();
		void stop();

		const RunArgs& getArgs() const;
		ConfigManager& getConfigManager();
		NetworkManager& getNetworkManager();

		static AnticheatProxy* get();
	};
}
