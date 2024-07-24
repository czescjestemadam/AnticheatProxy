#include "system_chat_message.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::SystemChatMessage::read(const ProtocolVersion* version)
{
	message = buf.readNbt(*version < ProtocolVersion::v1_20_2);
	overlay = buf.readByte();
}

void acp::packet::play::s2c::SystemChatMessage::write(const ProtocolVersion* version)
{
	buf.writeNbt(message, *version < ProtocolVersion::v1_20_2);
	buf.writeByte(overlay);
}

bool acp::packet::play::s2c::SystemChatMessage::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
}

int acp::packet::play::s2c::SystemChatMessage::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x6C;
	if (*version >= ProtocolVersion::v1_20_3)
		return 0x69;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x67;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x64;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x60;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x62;
	if (*version >= ProtocolVersion::v1_19)
		return 0x5F;

	return -1;
}

std::unique_ptr<acp::nbt::Tag>& acp::packet::play::s2c::SystemChatMessage::getMessage()
{
	return message;
}

void acp::packet::play::s2c::SystemChatMessage::setMessage(std::unique_ptr<nbt::Tag>&& message)
{
	this->message = std::move(message);
}

bool acp::packet::play::s2c::SystemChatMessage::isOverlay() const
{
	return overlay;
}

void acp::packet::play::s2c::SystemChatMessage::setOverlay(bool overlay)
{
	this->overlay = overlay;
}

std::string acp::packet::play::s2c::SystemChatMessage::toString() const
{
	return std::format("SystemChatMessage[msg={}, overlay={}]", message->toString(), overlay);
}
