#include "anticheat_proxy.hh"

#include "globals.hh"
#include "util/logger/root_logger.hh"
#include "util/terminal/prompt.hh"

static acp::AnticheatProxy* INST;

acp::AnticheatProxy::AnticheatProxy(RunArgs&& args)
	: args(std::move(args)),
	  configManager(this->args),
	  networkManager(configManager.getNetwork().listenIp, configManager.getNetwork().listenPort,
					 configManager.getNetwork().destinationIp, configManager.getNetwork().destinationPort)
{
	INST = this;
}

void acp::AnticheatProxy::start()
{
	RootLogger::get()->info("Starting AnticheatProxy {}", globals::VERSION);

	networkManager.start();
}

void acp::AnticheatProxy::stop()
{
	RootLogger::get()->info("Stopping AnticheatProxy");

	networkManager.stop();

	terminal::prompt::stop();
}

void acp::AnticheatProxy::wait()
{
	networkManager.wait();
}

const acp::RunArgs& acp::AnticheatProxy::getArgs() const
{
	return args;
}

acp::ConfigManager& acp::AnticheatProxy::getConfigManager()
{
	return configManager;
}

acp::PermissionManager& acp::AnticheatProxy::getPermissionManager()
{
	return permissionManager;
}

acp::NetworkManager& acp::AnticheatProxy::getNetworkManager()
{
	return networkManager;
}

acp::CommandManager& acp::AnticheatProxy::getCommandManager()
{
	return commandManager;
}


acp::AnticheatProxy* acp::AnticheatProxy::get()
{
	return INST;
}
