#include "signed_chat_command.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::c2s::SignedChatCommand::read(const ProtocolVersion* version)
{
	command = buf.readStr();
	timestamp = buf.readLong();
	salt = buf.readLong();

	const int len = buf.readVarint();
	for (int i = 0; i < len; ++i)
	{
		const std::string name = buf.readStr();

		const int argLen = *version >= ProtocolVersion::v1_19_3 ? 256 : buf.readVarint();
		const ByteBuf signature = buf.readBuf(argLen);

		argumentSignatures.emplace_back(name, signature);
	}

	if (*version < ProtocolVersion::v1_19_3)
		signedPreview = buf.readByte();
	else
	{
		messageCount = buf.readVarint();
	}
}

void acp::packet::play::c2s::SignedChatCommand::write(const ProtocolVersion* version)
{
	buf.writeStr(command);
	buf.writeLong(timestamp);
	buf.writeLong(salt);

	buf.writeVarint(static_cast<int>(argumentSignatures.size()));
	for (auto& [name, signature] : argumentSignatures)
	{
		buf.writeStr(name);

		if (*version < ProtocolVersion::v1_19_3)
			buf.writeVarint(static_cast<int>(signature.size()));

		buf.writeBuf(signature);
	}

	if (*version < ProtocolVersion::v1_19_3)
		buf.writeByte(signedPreview.value());
	else
	{
		buf.writeVarint(messageCount.value());
	}
}

bool acp::packet::play::c2s::SignedChatCommand::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::c2s::SignedChatCommand::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x04;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x04;
	if (*version >= ProtocolVersion::v1_19)
		return 0x03;

	return -1;
}

std::string& acp::packet::play::c2s::SignedChatCommand::getCommand()
{
	return command;
}

void acp::packet::play::c2s::SignedChatCommand::setCommand(const std::string& command)
{
	this->command = command;
}

long acp::packet::play::c2s::SignedChatCommand::getTimestamp()
{
	return timestamp;
}

void acp::packet::play::c2s::SignedChatCommand::setTimestamp(long timestamp)
{
	this->timestamp = timestamp;
}

long acp::packet::play::c2s::SignedChatCommand::getSalt()
{
	return salt;
}

void acp::packet::play::c2s::SignedChatCommand::setSalt(long salt)
{
	this->salt = salt;
}

std::vector<std::pair<std::string, acp::ByteBuf>>& acp::packet::play::c2s::SignedChatCommand::getArgumentSignatures()
{
	return argumentSignatures;
}

void acp::packet::play::c2s::SignedChatCommand::setArgumentSignatures(const std::vector<std::pair<std::string, ByteBuf>>& argument_signatures)
{
	argumentSignatures = argument_signatures;
}

std::optional<bool>& acp::packet::play::c2s::SignedChatCommand::getSignedPreview()
{
	return signedPreview;
}

void acp::packet::play::c2s::SignedChatCommand::setSignedPreview(const std::optional<bool>& signed_preview)
{
	signedPreview = signed_preview;
}

std::optional<int>& acp::packet::play::c2s::SignedChatCommand::getMessageCount()
{
	return messageCount;
}

void acp::packet::play::c2s::SignedChatCommand::setMessageCount(const std::optional<int>& message_count)
{
	messageCount = message_count;
}

std::string acp::packet::play::c2s::SignedChatCommand::toString() const
{
	return std::format("SignedChatCommand[cmd={}, ts={} salt={}, args={}]", command, timestamp, salt, argumentSignatures.size());
}
