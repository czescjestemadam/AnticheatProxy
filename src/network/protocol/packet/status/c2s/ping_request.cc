#include "ping_request.hh"

#include <format>

void acp::packet::status::c2s::PingRequest::read()
{
	timestamp = buf.readLong();
}

void acp::packet::status::c2s::PingRequest::write()
{
	buf.writeLong(timestamp);
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
