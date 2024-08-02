#include "anticheat_proxy.hh"

#include "globals.hh"
#include "util/logger/root_logger.hh"

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

	networkManager.wait();
}

void acp::AnticheatProxy::stop()
{
	RootLogger::get()->info("Stopping AnticheatProxy");

	networkManager.stop();
}

const acp::RunArgs& acp::AnticheatProxy::getArgs() const
{
	return args;
}

acp::ConfigManager& acp::AnticheatProxy::getConfigManager()
{
	return configManager;
}

acp::NetworkManager& acp::AnticheatProxy::getNetworkManager()
{
	return networkManager;
}


acp::AnticheatProxy* acp::AnticheatProxy::get()
{
	return INST;
}
