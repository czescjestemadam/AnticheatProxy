#include "login_acknowledged.hh"

void acp::packet::login::c2s::LoginAcknowledged::read(const ProtocolVersion* version)
{
}

void acp::packet::login::c2s::LoginAcknowledged::write(const ProtocolVersion* version)
{
}

int acp::packet::login::c2s::LoginAcknowledged::getId(const ProtocolVersion* version) const
{
	return 0x03;
}

std::string acp::packet::login::c2s::LoginAcknowledged::toString() const
{
	return "LoginAcknowledged";
}
