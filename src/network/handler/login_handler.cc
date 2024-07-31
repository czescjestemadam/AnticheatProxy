#include "login_handler.hh"

#include "network/connection.hh"

acp::HandleResult acp::LoginHandler::handle(packet::login::c2s::CookieResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::LoginHandler::handle(packet::login::c2s::EncryptionResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::LoginHandler::handle(packet::login::c2s::LoginAcknowledged* packet)
{
	connection->setState(NetworkState::CONFIGURATION);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::LoginHandler::handle(packet::login::c2s::LoginPluginResponse* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::LoginHandler::handle(packet::login::c2s::LoginStart* packet)
{
	return HandleResult::FORWARD;
}


acp::HandleResult acp::LoginHandler::handle(packet::login::s2c::CookieRequest* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::LoginHandler::handle(packet::login::s2c::Disconnect* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::LoginHandler::handle(packet::login::s2c::EncryptionRequest* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::LoginHandler::handle(packet::login::s2c::LoginPluginRequest* packet)
{
	return HandleResult::FORWARD;
}

acp::HandleResult acp::LoginHandler::handle(packet::login::s2c::LoginSuccess* packet)
{
	connection->getLogger().info("{} ({}) logged in", packet->getUsername(), packet->getUuid().toString());

	connection->setGameProfile(packet->toGameProfile());

	if (*connection->getProtocolVersion() <= ProtocolVersion::v1_20)
		connection->setState(NetworkState::PLAY);

	return HandleResult::FORWARD;
}

acp::HandleResult acp::LoginHandler::handle(packet::login::s2c::SetCompression* packet)
{
	connection->setCompressionThreshold(packet->getThreshold());

	return HandleResult::FORWARD;
}
