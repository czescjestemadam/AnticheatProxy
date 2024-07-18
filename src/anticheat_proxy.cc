#include "anticheat_proxy.hh"

#include "globals.hh"

constexpr const char* LISTEN_ADDR = "0.0.0.0";
constexpr ushort LISTEN_PORT = 30066;

constexpr const char* KRYSTAL_ADDR = "146.59.52.73";
constexpr const char* SERVER_ADDR = "192.168.0.234";
constexpr ushort SERVER_PORT = 30077;

static acp::AnticheatProxy* INST;

acp::AnticheatProxy::AnticheatProxy(RunArgs&& args)
	: args(std::move(args)),
	  networkManager(LISTEN_ADDR, LISTEN_PORT, SERVER_ADDR, SERVER_PORT)
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
