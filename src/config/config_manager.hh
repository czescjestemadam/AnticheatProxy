#pragma once
#include "network_config.hh"
#include "run_args.hh"
#include "util/logger/sub_logger.hh"

namespace acp
{
	class ConfigManager
	{
		SubLogger logger = SubLogger::fromRoot("ConfigManager");

		NetworkConfig network;

	public:
		explicit ConfigManager(const RunArgs& args);

		void load();
		void save();

		NetworkConfig& getNetwork();
	};
}
