#include "status_request.hh"

void acp::packet::status::c2s::StatusRequest::read(const ProtocolVersion* version)
{
}

void acp::packet::status::c2s::StatusRequest::write(const ProtocolVersion* version)
{
}

int acp::packet::status::c2s::StatusRequest::getId(const ProtocolVersion* version) const
{
	return 0x01;
}

std::string acp::packet::status::c2s::StatusRequest::toString() const
{
	return "StatusRequest";
}
