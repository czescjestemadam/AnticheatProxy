#include "login_handler.hh"

bool acp::LoginHandler::handle(packet::login::c2s::CookieResponse* packet)
{
	return false;
}

bool acp::LoginHandler::handle(packet::login::c2s::EncryptionResponse* packet)
{
	return false;
}

bool acp::LoginHandler::handle(packet::login::c2s::LoginAcknowledged* packet)
{
	return false;
}

bool acp::LoginHandler::handle(packet::login::c2s::LoginPluginResponse* packet)
{
	return false;
}

bool acp::LoginHandler::handle(packet::login::c2s::LoginStart* packet)
{
	return false;
}


bool acp::LoginHandler::handle(packet::login::s2c::CookieRequest* packet)
{
	return false;
}

bool acp::LoginHandler::handle(packet::login::s2c::Disconnect* packet)
{
	return false;
}

bool acp::LoginHandler::handle(packet::login::s2c::EncryptionRequest* packet)
{
	return false;
}

bool acp::LoginHandler::handle(packet::login::s2c::LoginPluginRequest* packet)
{
	return false;
}

bool acp::LoginHandler::handle(packet::login::s2c::LoginSuccess* packet)
{
	return false;
}

bool acp::LoginHandler::handle(packet::login::s2c::SetCompression* packet)
{
	return false;
}
