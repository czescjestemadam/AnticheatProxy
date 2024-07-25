#include "status_response.hh"

#include "network/handler/status_handler.hh"

#include <format>

void acp::packet::status::s2c::StatusResponse::read(const ProtocolVersion* version)
{
	json = buf.readStr();
}

void acp::packet::status::s2c::StatusResponse::write(const ProtocolVersion* version)
{
	buf.writeStr(json);
}

acp::HandleResult acp::packet::status::s2c::StatusResponse::apply(std::unique_ptr<INetworkHandler>& handler)
{
	if (auto* statusHandler = dynamic_cast<StatusHandler*>(handler.get()))
		return statusHandler->handle(this);

	return HandleResult::FORWARD;
}

int acp::packet::status::s2c::StatusResponse::getId(const ProtocolVersion* version) const
{
	return 0x00;
}

std::string acp::packet::status::s2c::StatusResponse::getJson() const
{
	return json;
}

void acp::packet::status::s2c::StatusResponse::setJson(const std::string& json)
{
	this->json = json;
}

std::string acp::packet::status::s2c::StatusResponse::toString() const
{
	return std::format("StatusResponse[{}]", json);
}
