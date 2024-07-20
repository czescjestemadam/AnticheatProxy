#include "disconnect.hh"

#include "network/handler/play_handler.hh"
#include "network/protocol/protocol_version.hh"

void acp::packet::play::s2c::Disconnect::read(const ProtocolVersion* version)
{
	reason = buf.readStr();
}

void acp::packet::play::s2c::Disconnect::write(const ProtocolVersion* version)
{
	buf.writeStr(reason);
}

bool acp::packet::play::s2c::Disconnect::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* playHandler = dynamic_cast<PlayHandler*>(handler.get()))
		return playHandler->handle(this);

	return false;
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

std::string& acp::packet::play::s2c::Disconnect::getReason()
{
	return reason;
}

void acp::packet::play::s2c::Disconnect::setReason(const std::string& reason)
{
	this->reason = reason;
}

std::string acp::packet::play::s2c::Disconnect::toString() const
{
	return std::format("Disconnect[{}]", reason);
}
