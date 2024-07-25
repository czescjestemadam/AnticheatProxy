#include "handshake_handler.hh"

#include "network/connection.hh"

acp::HandleResult acp::HandshakeHandler::handle(packet::handshake::Handshake* packet)
{
	const ProtocolVersion* protocolVersion = ProtocolVersion::byIdx(packet->getProtocolVersion());
	if (protocolVersion)
		connection->setProtocolVersion(protocolVersion);

	const NetworkState nextState = packet->getNextState() == 1 ? NetworkState::STATUS : NetworkState::LOGIN;

	connection->getLogger().info("Switching to {} with {}",
								 EnumNames<NetworkState>::get(nextState),
								 protocolVersion->getName()
	);

	connection->setState(nextState);

	return HandleResult::FORWARD;
}
