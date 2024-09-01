#include "pid_file_lock.hh"

#include <filesystem>
#include <fstream>
#include <unistd.h>

#include "globals.hh"

acp::PidFileLock::PidFileLock()
{
	const std::filesystem::path file = globals::RUNDIR / ".pid";

	if (exists(file))
	{
		std::ifstream ifs(file);
		if (!ifs.good())
			throw std::runtime_error("pid file fstream::good() == false");

		int pid;

		ifs >> pid;
		ifs.close();

		if (std::filesystem::exists("/proc/" + std::to_string(pid)))
			throw std::runtime_error("AnticheatProxy is already running in this directory");
	}

	std::ofstream ofs(file);
	if (!ofs.good())
		throw std::runtime_error("pid file fstream::good() == false");

	ofs << getpid();
	ofs.close();
}

acp::PidFileLock::~PidFileLock()
{
	std::filesystem::remove(globals::RUNDIR / ".pid");
}
