#include "status_request.hh"

#include "network/handler/status_handler.hh"

void acp::packet::status::c2s::StatusRequest::read(const ProtocolVersion* version)
{
}

void acp::packet::status::c2s::StatusRequest::write(const ProtocolVersion* version)
{
}

bool acp::packet::status::c2s::StatusRequest::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* statusHandler = dynamic_cast<StatusHandler*>(handler.get()))
		return statusHandler->handle(this);

	return false;
}

int acp::packet::status::c2s::StatusRequest::getId(const ProtocolVersion* version) const
{
	return 0x01;
}

std::string acp::packet::status::c2s::StatusRequest::toString() const
{
	return "StatusRequest";
}
