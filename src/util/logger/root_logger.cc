#include "root_logger.hh"

#include "sub_logger.hh"
#include "util/terminal/format.hh"
#include "util/terminal/prompt.hh"

#include <chrono>
#include <iostream>

acp::RootLogger::RootLogger()
{
	const auto logsDir = getLogsDir();

	if (!exists(logsDir))
		create_directory(logsDir);

	filename = getFilename();
	openFile();
}

acp::RootLogger::~RootLogger()
{
	ofs.close();
}

std::filesystem::path acp::RootLogger::getLogsDir() const
{
	return std::filesystem::current_path() / "logs";
}

std::string acp::RootLogger::getFilename() const
{
	return std::format("{:%Y-%m-%d}.log", std::chrono::current_zone()->to_local(std::chrono::system_clock::now()));
}

void acp::RootLogger::openFile()
{
	ofs.close();

	ofs = { getLogsDir() / filename, std::ios::app };
	if (!ofs.good())
		throw std::runtime_error("RootLogger fstream::good() = false");
}


void acp::RootLogger::log(LogLevel level, const std::string& message)
{
	const auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(
		std::chrono::current_zone()->to_local(std::chrono::system_clock::now())
	);

	const std::string rawLine = std::format("[{:%T} {}]: {}", time, EnumNames<LogLevel>::get(level), message);

	const auto formatPrefix = level >= LogLevel::ERROR
								  ? terminal::Format::FG_RED
								  : level >= LogLevel::WARN
										? terminal::Format::FG_YELLOW
										: terminal::Format::RESET;

	std::ostream& os = level >= LogLevel::ERROR ? std::cerr : std::cout;
	os << std::format("\r{}{}{}\n", formatPrefix.toString(), rawLine, terminal::Format::RESET.toString());

	terminal::prompt::print();

	if (filename != getFilename())
	{
		filename = getFilename();
		openFile();
	}

	if (ofs.is_open())
		ofs << rawLine << std::endl;
}

acp::SubLogger acp::RootLogger::getSubLogger(const std::string& name)
{
	return { this, name };
}

acp::RootLogger* acp::RootLogger::get()
{
	static RootLogger logger;
	return &logger;
}
