#include "root_logger.hh"

#include "sub_logger.hh"
#include "util/terminal/format.hh"

#include <chrono>
#include <iostream>

acp::RootLogger::RootLogger()
{
}

acp::RootLogger::~RootLogger()
{
}

void acp::RootLogger::log(LogLevel level, const std::string& message)
{
	const auto time = std::chrono::time_point_cast<std::chrono::milliseconds>(
		std::chrono::current_zone()->to_local(std::chrono::system_clock::now())
	);

	const std::string rawLine = std::format("[{:%T} {}]: {}\n", time, EnumNames<LogLevel>::get(level), message);

	const auto formatPrefix = level >= LogLevel::ERROR
								  ? terminal::Format::FG_RED
								  : level >= LogLevel::WARN
										? terminal::Format::FG_YELLOW
										: terminal::Format::RESET;

	std::ostream& os = level >= LogLevel::ERROR ? std::cerr : std::cout;
	os << std::format("\r{}{}{}", formatPrefix.toString(), rawLine, terminal::Format::RESET.toString());

	// TODO file
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
