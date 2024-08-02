#include "anticheat_proxy.hh"
#include "globals.hh"
#include "util/signal.hh"
#include "util/logger/root_logger.hh"
#include "util/terminal/prompt.hh"

#include <iostream>

int main(int argc, char* argv[])
{
	acp::signal::initHandlers();

	acp::RunArgs args(argc, argv);

	if (args.hasFlag("version"))
	{
		std::cout << "AnticheatProxy " << acp::globals::VERSION << " compiled at " << acp::globals::COMPILE_TIME << std::endl;
		return 0;
	}

	if (args.hasFlag("help"))
	{
		std::cout << "AnticheatProxy " << acp::globals::VERSION << " compiled at " << acp::globals::COMPILE_TIME << std::endl
				<< "\t--help              shows help" << std::endl
				<< "\t--version           shows proxy version" << std::endl
				<< "\t--default-configs   skips loading (and saving default) configs" << std::endl;
		return 0;
	}

	acp::RootLogger::get()->info("Loading...");
	acp::AnticheatProxy acp(std::move(args));
	acp.start();

	acp::terminal::prompt::start();

	acp.wait();

	return 0;
}
