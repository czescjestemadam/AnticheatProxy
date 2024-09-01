#include "signal.hh"

#include "anticheat_proxy.hh"

#include <csignal>

using clk = std::chrono::steady_clock;

static constexpr clk::duration DOUBLE_PRESS_TIME = std::chrono::milliseconds(500);
static clk::time_point lastSigint = clk::now();

void sigintHandler(int i)
{
	acp::SubLogger logger = acp::SubLogger::fromRoot("SignalHandler");

	logger.warn("SIGINT caught");
	if (clk::now() - lastSigint < DOUBLE_PRESS_TIME)
	{
		signal(SIGINT, SIG_DFL);
		acp::AnticheatProxy::get()->stop();
		return;
	}

	logger.warn("press again to stop AnticheatProxy");
	lastSigint = clk::now();
}

void acp::signal::initHandlers()
{
	::signal(SIGINT, &sigintHandler);
}
