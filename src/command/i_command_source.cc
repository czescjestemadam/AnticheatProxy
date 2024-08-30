#include "i_command_source.hh"

void acp::ICommandSource::sendMessage(const std::unique_ptr<text::Component>& message)
{
	sendMessage(message->copy());
}

bool acp::ICommandSource::hasPermission(const Permission* permission) const
{
	return permission == nullptr || hasPermission(*permission);
}
