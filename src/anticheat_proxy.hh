#pragma once
#include "run_args.hh"
#include "config/config_manager.hh"
#include "network/network_manager.hh"
#include "permission/permission_manager.hh"
#include "util/pid_file_lock.hh"

namespace acp
{
	class AnticheatProxy
	{
		PidFileLock _pidFileLock;

		RunArgs args;
		ConfigManager configManager;
		PermissionManager permissionManager;
		NetworkManager networkManager;

	public:
		explicit AnticheatProxy(RunArgs&& args);

		void start();
		void stop();
		void wait();

		const RunArgs& getArgs() const;
		ConfigManager& getConfigManager();
		PermissionManager& getPermissionManager();
		NetworkManager& getNetworkManager();

		static AnticheatProxy* get();
	};
}
