#pragma once
#include "run_args.hh"
#include "config/config_manager.hh"
#include "network/network_manager.hh"

namespace acp
{
	class AnticheatProxy
	{
		RunArgs args;
		ConfigManager configManager;
		NetworkManager networkManager;

	public:
		explicit AnticheatProxy(RunArgs&& args);

		void start();
		void stop();


		static AnticheatProxy* get();
	};
}
