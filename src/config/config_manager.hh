#pragma once
#include "util/logger/logger.hh"
#include "network_config.hh"

namespace acp
{
	class ConfigManager
	{
		Logger logger{ "ConfigManager" };

		NetworkConfig network;

	public:
		ConfigManager();

		void load();
		void save();

		NetworkConfig& getNetwork();
	};
}
