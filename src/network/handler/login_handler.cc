#include "login_handler.hh"

#include "network/connection.hh"

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
	connection->setState(NetworkState::CONFIGURATION);

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
	if (*connection->getProtocolVersion() <= ProtocolVersion::v1_20)
		connection->setState(NetworkState::PLAY);

	return false;
}

bool acp::LoginHandler::handle(packet::login::s2c::SetCompression* packet)
{
	connection->setCompressionThreshold(packet->getThreshold());

	return false;
}
