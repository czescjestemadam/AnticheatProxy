#include "status_handler.hh"

acp::HandleResult acp::StatusHandler::handle(packet::status::c2s::StatusRequest* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::StatusHandler::handle(packet::status::c2s::PingRequest* packet)
{
	return HandleResult::FORWARD;
}


acp::HandleResult acp::StatusHandler::handle(packet::status::s2c::StatusResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::StatusHandler::handle(packet::status::s2c::PingResponse* packet)
{
	return HandleResult::FORWARD;
}
