#include "status_handler.hh"

bool acp::StatusHandler::handle(packet::status::c2s::StatusRequest* packet)
{
	return false;
}

bool acp::StatusHandler::handle(packet::status::c2s::PingRequest* packet)
{
	return false;
}


bool acp::StatusHandler::handle(packet::status::s2c::StatusResponse* packet)
{
	return false;
}

bool acp::StatusHandler::handle(packet::status::s2c::PingResponse* packet)
{
	return false;
}
