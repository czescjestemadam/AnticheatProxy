#include "terminal_command_source.hh"

#include "util/logger/root_logger.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/terminal/terminal_io.hh"

void acp::TerminalCommandSource::sendMessage(std::unique_ptr<text::Component>&& message)
{
	RootLogger::get()->info(text::ITextIO::terminal().write(std::move(message)));
}

bool acp::TerminalCommandSource::hasPermission(const Permission& permission) const
{
	return true;
}
