#include "login_acknowledged.hh"

#include "network/protocol/protocol_version.hh"

void acp::packet::login::c2s::LoginAcknowledged::read(const ProtocolVersion* version)
{
}

void acp::packet::login::c2s::LoginAcknowledged::write(const ProtocolVersion* version)
{
}

int acp::packet::login::c2s::LoginAcknowledged::getId(const ProtocolVersion* version) const
{
	if (*version >= ProtocolVersion::v1_20_2)
		return 0x03;

	return -1;
}

std::string acp::packet::login::c2s::LoginAcknowledged::toString() const
{
	return "LoginAcknowledged";
}
