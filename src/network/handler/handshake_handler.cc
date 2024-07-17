#include "handshake_handler.hh"

#include "network/connection.hh"

bool acp::HandshakeHandler::handle(packet::handshake::Handshake* packet)
{
	const ProtocolVersion* protocolVersion = ProtocolVersion::byIdx(packet->getProtocolVersion());
	if (protocolVersion)
		connection->setProtocolVersion(protocolVersion);

	connection->setState(packet->getNextState() == 1 ? NetworkState::STATUS : NetworkState::LOGIN);

	return false;
}
