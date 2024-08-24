#include "disconnect.hh"

#include "network/handler/configuration_handler.hh"
#include "network/protocol/protocol_version.hh"
#include "util/text/io/i_text_io.hh"
#include "util/text/io/plaintext/plaintext_io.hh"

void acp::packet::configuration::s2c::Disconnect::read(const ProtocolVersion* version)
{
	reason = text::Component::fromNbt(buf.readNbt(false));
}

void acp::packet::configuration::s2c::Disconnect::write(const ProtocolVersion* version)
{
	std::unique_ptr<nbt::Tag> tag = std::make_unique<nbt::TagCompound>();
	reason->serialize(tag);
	buf.writeNbt(tag, false);
}

acp::HandleResult acp::packet::configuration::s2c::Disconnect::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* configHandler = dynamic_cast<ConfigurationHandler*>(handler.get()))
		return configHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::configuration::s2c::Disconnect::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_5)
		return 0x02;
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x01;

	return -1;
}

std::unique_ptr<acp::text::Component>& acp::packet::configuration::s2c::Disconnect::getReason()
{
	return reason;
}

const std::unique_ptr<acp::text::Component>& acp::packet::configuration::s2c::Disconnect::getReason() const
{
	return reason;
}

void acp::packet::configuration::s2c::Disconnect::setReason(std::unique_ptr<text::Component>&& component)
{
	this->reason = std::move(component);
}

std::string acp::packet::configuration::s2c::Disconnect::toString() const
{
	return std::format("Disconnect[{}]", text::ITextIO::plaintext().write(reason));
}
