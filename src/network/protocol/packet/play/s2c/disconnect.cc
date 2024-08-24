#include "disconnect.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/plaintext/plaintext_io.hh"

void acp::packet::play::s2c::Disconnect::read(const ProtocolVersion* version)
{
	reason = text::Component::fromNbt(buf.readNbt(*version < ProtocolVersion::v1_20_2));
}

void acp::packet::play::s2c::Disconnect::write(const ProtocolVersion* version)
{
	std::unique_ptr<nbt::Tag> tag = std::make_unique<nbt::TagCompound>();
	reason->serialize(tag);
	buf.writeNbt(tag, *version < ProtocolVersion::v1_20_2);
}

acp::HandleResult acp::packet::play::s2c::Disconnect::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::Disconnect::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x1D;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x1B;
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x1A;
	if (*version >= ProtocolVersion::v1_19_3)
		return 0x17;
	if (*version >= ProtocolVersion::v1_19_1)
		return 0x19;
	if (*version >= ProtocolVersion::v1_19)
		return 0x17;
	if (*version >= ProtocolVersion::v1_17)
		return 0x1A;

	return 0x19;
}

std::unique_ptr<acp::text::Component>& acp::packet::play::s2c::Disconnect::getReason()
{
	return reason;
}

const std::unique_ptr<acp::text::Component>& acp::packet::play::s2c::Disconnect::getReason() const
{
	return reason;
}

void acp::packet::play::s2c::Disconnect::setReason(std::unique_ptr<text::Component>&& reason)
{
	this->reason = std::move(reason);
}

std::string acp::packet::play::s2c::Disconnect::toString() const
{
	return std::format("Disconnect[{}]", text::ITextIO::plaintext().write(reason));
}
