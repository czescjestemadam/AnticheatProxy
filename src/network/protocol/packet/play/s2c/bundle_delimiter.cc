#include "bundle_delimiter.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::BundleDelimiter::read(const ProtocolVersion* version)
{
}

void acp::packet::play::s2c::BundleDelimiter::write(const ProtocolVersion* version)
{
}

acp::HandleResult acp::packet::play::s2c::BundleDelimiter::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::play::s2c::BundleDelimiter::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_19_4)
		return 0x00;

	return -1;
}

std::string acp::packet::play::s2c::BundleDelimiter::toString() const
{
	return "BundleDelimiter";
}
