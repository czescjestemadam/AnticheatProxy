#include "status_response.hh"

#include <format>

void acp::packet::status::s2c::StatusResponse::read()
{
	json = buf.readStr();
}

void acp::packet::status::s2c::StatusResponse::write()
{
	buf.writeStr(json);
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
