#include "system_chat_message.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::SystemChatMessage::read(const ProtocolVersion* version)
{
	content = buf.readStr();
	overlay = buf.readByte();
}

void acp::packet::play::s2c::SystemChatMessage::write(const ProtocolVersion* version)
{
	buf.writeStr(content);
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

std::string& acp::packet::play::s2c::SystemChatMessage::getContent()
{
	return content;
}

void acp::packet::play::s2c::SystemChatMessage::setContent(const std::string& content)
{
	this->content = content;
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
	return std::format("SystemChatMessage[content={}, overlay={}]", content, overlay);
}
