#include "ping_response.hh"

#include <format>

void acp::packet::status::s2c::PingResponse::read(const ProtocolVersion* version)
{
	timestamp = buf.readLong();
}

void acp::packet::status::s2c::PingResponse::write(const ProtocolVersion* version)
{
	buf.writeLong(timestamp);
}

int acp::packet::status::s2c::PingResponse::getId(const ProtocolVersion* version) const
{
	return 1;
}

long acp::packet::status::s2c::PingResponse::getTimestamp() const
{
	return timestamp;
}

void acp::packet::status::s2c::PingResponse::setTimestamp(long timestamp)
{
	this->timestamp = timestamp;
}

std::string acp::packet::status::s2c::PingResponse::toString() const
{
	return std::format("PingResponse[{}]", timestamp);
}
