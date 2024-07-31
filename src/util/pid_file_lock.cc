#include "pid_file_lock.hh"

#include <filesystem>
#include <fstream>
#include <unistd.h>

constexpr const char* PIDFILE = ".pid";

acp::PidFileLock::PidFileLock()
{
	if (std::filesystem::exists(PIDFILE))
	{
		std::ifstream ifs(PIDFILE);
		if (!ifs.good())
			throw std::runtime_error("pid file fstream::good() == false");

		int pid;

		ifs >> pid;
		ifs.close();

		if (std::filesystem::exists("/proc/" + std::to_string(pid)))
			throw std::runtime_error("AnticheatProxy is already running in this directory");
	}

	std::ofstream ofs(PIDFILE);
	if (!ofs.good())
		throw std::runtime_error("pid file fstream::good() == false");

	ofs << getpid();
	ofs.close();
}

acp::PidFileLock::~PidFileLock()
{
	std::filesystem::remove(PIDFILE);
}
