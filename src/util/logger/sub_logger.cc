#include "sub_logger.hh"

#include "root_logger.hh"

acp::SubLogger::SubLogger(ILogger* parent, const std::string& name) : parent(parent), name(name)
{
}

void acp::SubLogger::log(LogLevel level, const std::string& message)
{
	parent->log(level, std::format("[{}] {}", name, message));
}

acp::SubLogger acp::SubLogger::getSubLogger(const std::string& name)
{
	return { this, name };
}

const std::string& acp::SubLogger::getName() const
{
	return name;
}

void acp::SubLogger::setName(const std::string& name)
{
	this->name = name;
}


acp::SubLogger acp::SubLogger::fromRoot(const std::string& name)
{
	return RootLogger::get()->getSubLogger(name);
}
