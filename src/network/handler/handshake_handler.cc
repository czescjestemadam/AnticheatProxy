#include "handshake_handler.hh"

#include "network/connection.hh"

#include <iostream>

bool acp::HandshakeHandler::handle(packet::handshake::Handshake* packet)
{
	const ProtocolVersion* protocolVersion = ProtocolVersion::byIdx(packet->getProtocolVersion());
	if (protocolVersion)
		connection->setProtocolVersion(protocolVersion);

	const NetworkState nextState = packet->getNextState() == 1 ? NetworkState::STATUS : NetworkState::LOGIN;

	std::cout << std::format("{} switching to {} with {}\n",
							 connection->getSide(NetworkSide::CLIENT).getAddrStr(),
							 EnumNames<NetworkState>::get(nextState),
							 protocolVersion->getName()
	);

	connection->setState(nextState);

	return false;
}
