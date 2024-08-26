#pragma once
#include "alert_config.hh"
#include "network_config.hh"
#include "profiler_config.hh"
#include "run_args.hh"
#include "util/logger/sub_logger.hh"

namespace acp
{
	class ConfigManager
	{
		SubLogger logger = SubLogger::fromRoot("ConfigManager");

		NetworkConfig network;
		AlertConfig alert;
		ProfilerConfig profiler;

	public:
		explicit ConfigManager(const RunArgs& args);

		void load();
		void save();

		NetworkConfig& getNetwork();
		AlertConfig& getAlert();
		ProfilerConfig& getProfiler();
	};
}
