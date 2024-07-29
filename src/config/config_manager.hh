#pragma once
#include "util/logger/logger.hh"
#include "network_config.hh"
#include "run_args.hh"

namespace acp
{
	class ConfigManager
	{
		Logger logger{ "ConfigManager" };

		NetworkConfig network;

	public:
		explicit ConfigManager(const RunArgs& args);

		void load();
		void save();

		NetworkConfig& getNetwork();
	};
}
