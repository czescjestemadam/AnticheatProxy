#include "ping_response.hh"

#include "network/handler/status_handler.hh"

#include <format>

void acp::packet::status::s2c::PingResponse::read(const ProtocolVersion* version)
{
	timestamp = buf.readLong();
}

void acp::packet::status::s2c::PingResponse::write(const ProtocolVersion* version)
{
	buf.writeLong(timestamp);
}

acp::HandleResult acp::packet::status::s2c::PingResponse::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* statusHandler = dynamic_cast<StatusHandler*>(handler.get()))
		return statusHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::status::s2c::PingResponse::getId(const ProtocolVersion* version) const
{
	return 0x01;
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
