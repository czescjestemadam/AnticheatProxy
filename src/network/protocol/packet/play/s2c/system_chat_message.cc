#include "system_chat_message.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/plaintext/plaintext_io.hh"

void acp::packet::play::s2c::SystemChatMessage::read(const ProtocolVersion* version)
{
	message = text::Component::fromNbt(buf.readNbt(*version < ProtocolVersion::v1_20_2));
	overlay = buf.readByte();
}

void acp::packet::play::s2c::SystemChatMessage::write(const ProtocolVersion* version)
{
	std::unique_ptr<nbt::Tag> tag = std::make_unique<nbt::TagCompound>();
	message->serialize(tag);
	buf.writeNbt(tag, *version < ProtocolVersion::v1_20_2);
	buf.writeByte(overlay);
}

acp::HandleResult acp::packet::play::s2c::SystemChatMessage::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
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

std::unique_ptr<acp::text::Component>& acp::packet::play::s2c::SystemChatMessage::getMessage()
{
	return message;
}

void acp::packet::play::s2c::SystemChatMessage::setMessage(std::unique_ptr<text::Component>&& message)
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
	return std::format("SystemChatMessage[msg={}, overlay={}]", text::ITextIO::plaintext().write(message), overlay);
}
