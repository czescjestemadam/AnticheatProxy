#include "anticheat_proxy.hh"

#include "globals.hh"

static acp::AnticheatProxy* INST;

acp::AnticheatProxy::AnticheatProxy(RunArgs&& args)
	: args(std::move(args)),
	  networkManager(configManager.getNetwork().listenIp, configManager.getNetwork().listenPort,
					 configManager.getNetwork().destinationIp, configManager.getNetwork().destinationPort)
{
	INST = this;
}

void acp::AnticheatProxy::start()
{
	logger.info("Starting AnticheatProxy {}", globals::VERSION);

	networkManager.start();
	networkManager.wait();
}

void acp::AnticheatProxy::stop()
{
	logger.info("Stopping AnticheatProxy");
	networkManager.stop();
}


acp::AnticheatProxy* acp::AnticheatProxy::get()
{
	return INST;
}
