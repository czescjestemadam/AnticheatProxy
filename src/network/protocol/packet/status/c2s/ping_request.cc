#include "ping_request.hh"

#include "network/handler/status_handler.hh"

#include <format>

void acp::packet::status::c2s::PingRequest::read(const ProtocolVersion* version)
{
	timestamp = buf.readLong();
}

void acp::packet::status::c2s::PingRequest::write(const ProtocolVersion* version)
{
	buf.writeLong(timestamp);
}

bool acp::packet::status::c2s::PingRequest::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* statusHandler = dynamic_cast<StatusHandler*>(handler.get()))
		return statusHandler->handle(this);

	return false;
}

int acp::packet::status::c2s::PingRequest::getId(const ProtocolVersion* version) const
{
	return 0x01;
}

long acp::packet::status::c2s::PingRequest::getTimestamp() const
{
	return timestamp;
}

void acp::packet::status::c2s::PingRequest::setTimestamp(long timestamp)
{
	this->timestamp = timestamp;
}

std::string acp::packet::status::c2s::PingRequest::toString() const
{
	return std::format("PingRequest[{}]", timestamp);
}
