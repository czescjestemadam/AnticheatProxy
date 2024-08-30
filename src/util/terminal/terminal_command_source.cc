#include "terminal_command_source.hh"

#include "util/logger/root_logger.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/plaintext/plaintext_io.hh"

void acp::TerminalCommandSource::sendMessage(std::unique_ptr<text::Component>&& message)
{
	// todo terminal text io
	RootLogger::get()->info(text::ITextIO::plaintext().write(message));
}

bool acp::TerminalCommandSource::hasPermission(const Permission& permission) const
{
	return true;
}
