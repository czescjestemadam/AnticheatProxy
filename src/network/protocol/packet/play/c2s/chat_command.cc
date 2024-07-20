#include "chat_command.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::ChatCommand::read(const ProtocolVersion* version)
{
	command = buf.readStr();
}

void acp::packet::play::c2s::ChatCommand::write(const ProtocolVersion* version)
{
	buf.writeStr(command);
}

bool acp::packet::play::c2s::ChatCommand::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::c2s::ChatCommand::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x04;

	return -1;
}

std::string& acp::packet::play::c2s::ChatCommand::getCommand()
{
	return command;
}

void acp::packet::play::c2s::ChatCommand::setCommand(const std::string& command)
{
	this->command = command;
}

std::string acp::packet::play::c2s::ChatCommand::toString() const
{
	return std::format("ChatCommand[{}]", command);
}
