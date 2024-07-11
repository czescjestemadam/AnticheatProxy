#include "anticheat_proxy.hh"
#include "globals.hh"

#include <iostream>

int main(int argc, char* argv[])
{
	acp::RunArgs args(argc, argv);

	if (args.hasFlag("version"))
	{
		std::cout << "AnticheatProxy " << acp::globals::VERSION << " compiled at " << acp::globals::COMPILE_TIME << std::endl;
		return 0;
	}

	if (args.hasFlag("help"))
	{
		std::cout << "AnticheatProxy " << acp::globals::VERSION << " compiled at " << acp::globals::COMPILE_TIME << std::endl
				<< "\t--help      shows help" << std::endl
				<< "\t--version   shows proxy version" << std::endl;
		return 0;
	}

	acp::AnticheatProxy acp(std::move(args));
	acp.start();


	return 0;
}
