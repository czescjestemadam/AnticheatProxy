#include "login_acknowledged.hh"

void acp::packet::login::c2s::LoginAcknowledged::read(const ProtocolVersion* version)
{
}

void acp::packet::login::c2s::LoginAcknowledged::write(const ProtocolVersion* version)
{
}

std::string acp::packet::login::c2s::LoginAcknowledged::toString() const
{
	return "LoginAcknowledged";
}
