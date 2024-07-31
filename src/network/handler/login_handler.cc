#include "login_handler.hh"

#include "network/connection.hh"
#include "util/velocity/forwarding_info.hh"

#include <arpa/inet.h>

const acp::Identifier VELOCITY_PLAYER_INFO_CHANNEL = { "velocity", "player_info" };

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
	if (velocityMessageId.has_value() && packet->getMessageId() == velocityMessageId.value())
	{
		ByteBuf data = packet->getData();

		velocity::ForwardingInfo info;
		info.deserialize(data);

		PlayerSocket& socket = connection->getSide(NetworkSide::CLIENT);

		sockaddr_in address = socket.getAddr();
		address.sin_addr.s_addr = inet_addr(info.address.c_str());

		socket.setAddr(std::move(address));

		connection->getLogger().setName("Connection " + socket.getAddrStr());
		connection->getLogger().info("Forwarded address received from velocity");
	}

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
	if (packet->getChannel() == VELOCITY_PLAYER_INFO_CHANNEL)
		velocityMessageId = packet->getMessageId();

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
