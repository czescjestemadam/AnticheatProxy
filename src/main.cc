#include "anticheat_proxy.hh"
#include "globals.hh"
#include "util/signal.hh"
#include "util/logger/root_logger.hh"
#include "util/profiler/profiler.hh"
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
				<< "\t--default-configs   skips loading (and saving default) configs" << std::endl
				<< "\t--rundir <path>     sets directory to run in" << std::endl;
		return 0;
	}

	if (args.getArg("rundir"))
	{
		const std::filesystem::path argDir = args.getArg("rundir").value();
		if (exists(argDir))
			acp::globals::RUNDIR = argDir;
	}

	acp::RootLogger::get()->info("Loading...");
	acp::AnticheatProxy acp(std::move(args));
	try
	{
		acp.start();
	}
	catch (const std::exception& ex)
	{
		acp::RootLogger::get()->error("cant start: {}", ex.what());
		return 1;
	}

	acp::terminal::prompt::start();

	acp.wait();

	std::string profilerDump = std::format("== Profiler samples collected from {} to {} ==\n",
										   std::chrono::time_point_cast<std::chrono::seconds>(acp::globals::STARTED_AT),
										   std::chrono::time_point_cast<std::chrono::seconds>(
											   std::chrono::current_zone()->to_local(std::chrono::system_clock::now())
										   )
	);
	constexpr auto seconds = [](const std::chrono::system_clock::duration& dur)
	{
		return static_cast<float>(dur.count()) / static_cast<float>(std::chrono::system_clock::duration::period::den);
	};
	for (const auto& [name, sample] : acp::Profiler::get().compileSamples())
	{
		profilerDump += std::format("{}: count = {}, first {}, last {}\n"
									"\t\tmin {:.06f}s ({}) -> max {:.06f}s ({})\n"
									"\t\tavg {:.06f}s ({}), median {:.06f}s ({})\n"
									"\t\ttime sum: {:.06f}s ({})\n",
									name, sample.count,
									std::chrono::current_zone()->to_local(sample.first), std::chrono::current_zone()->to_local(sample.last),
									seconds(sample.min), sample.min,
									seconds(sample.max), sample.max,
									seconds(sample.avg), sample.avg,
									seconds(sample.median), sample.median,
									seconds(sample.time), sample.time
		);
	}

	const acp::ProfilerConfig& profilerConfig = acp.getConfigManager().getProfiler();
	if (profilerConfig.loggerDump)
		acp::RootLogger::get()->info(profilerDump);
	if (profilerConfig.fileDump)
	{
		const std::filesystem::path profilerDumpsDir = acp::globals::RUNDIR / "profiler-dumps";
		if (!exists(profilerDumpsDir))
			create_directory(profilerDumpsDir);

		const std::string filename = std::format("{:%Y-%m-%d_%T}",
												 std::chrono::time_point_cast<std::chrono::seconds>(
													 std::chrono::current_zone()->to_local(std::chrono::system_clock::now())
												 )
		);
		const std::filesystem::path profilerDumpFile = profilerDumpsDir / filename;
		std::ofstream ofs(profilerDumpFile);
		if (ofs.good())
			ofs << profilerDump << std::flush;
		else if (!profilerConfig.loggerDump)
		{
			acp::RootLogger::get()->warn("error dumping profiler samples to {}, dumping to logger instead", profilerDumpFile.c_str());
			acp::RootLogger::get()->info(profilerDump);
		}
	}

	return 0;
}
