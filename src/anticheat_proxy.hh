#pragma once
#include "run_args.hh"
#include "anticheat/alert/alert_manager.hh"
#include "command/command_manager.hh"
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
		AlertManager alertManager;
		CommandManager commandManager;

	public:
		explicit AnticheatProxy(RunArgs&& args);

		void start();
		void stop();
		void wait();

		const RunArgs& getArgs() const;
		ConfigManager& getConfigManager();
		PermissionManager& getPermissionManager();
		NetworkManager& getNetworkManager();
		AlertManager& getAlertManager();
		CommandManager& getCommandManager();

		static AnticheatProxy* get();
	};
}
