#include "logger.hh"

#include "util/terminal/format.hh"

#include <chrono>
#include <iostream>

acp::Logger::Logger(const std::string& name): name(name)
{
}

void acp::Logger::log(LogLevel level, const std::string& message)
{
	const auto time = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());

	std::ostream& os = level >= LogLevel::ERROR ? std::cerr : std::cout;
	os << std::format("\r{}[{:%T} {}]: {}{}\n",
					  (level >= LogLevel::ERROR
						   ? terminal::Format::FG_RED
						   : level >= LogLevel::WARN
								 ? terminal::Format::FG_YELLOW
								 : terminal::Format::RESET).toString(),
					  std::chrono::time_point_cast<std::chrono::milliseconds>(time),
					  EnumNames<LogLevel>::get(level),
					  (name.empty() ? "" : "[" + name + "] ") + message,
					  terminal::Format::RESET.toString()
	);
}

const std::string& acp::Logger::getName() const
{
	return name;
}

void acp::Logger::setName(const std::string& name)
{
	this->name = name;
}
