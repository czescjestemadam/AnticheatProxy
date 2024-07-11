#include "connection.hh"

#include "handler/configuration_handler.hh"
#include "handler/login_handler.hh"
#include "handler/play_handler.hh"
#include "handler/status_handler.hh"

#include <iostream>

acp::Connection::Connection(PlayerSocket&& clientSocket, PlayerSocket&& destSocket)
	: clientSocket(std::move(clientSocket)),
	  destSocket(std::move(destSocket))
{
	setState(NetworkState::HANDSHAKE);
}

void acp::Connection::close()
{
	// TODO reason
	networkHandler->disconnect();

	destSocket.close();
	clientSocket.close();
}

void acp::Connection::handleEvent(int fd)
{
	const NetworkSide fromSide = fd == clientSocket.getFd() ? NetworkSide::CLIENT : NetworkSide::DEST;
	const NetworkSide toSide = getOppositeSide(fromSide);
	PlayerSocket& from = getSide(fromSide);
	PlayerSocket& to = getSide(toSide);

	ByteBuf buf = from.read();

	{
		ByteBuf packet = buf;

	}


	to.write(buf);

	std::cout << std::format("[{}]: sent {} bytes\n", toString(toSide), buf.size());
}

acp::PlayerSocket& acp::Connection::getSide(NetworkSide side)
{
	if (side == NetworkSide::CLIENT)
		return clientSocket;

	return destSocket;
}

acp::NetworkState acp::Connection::getState() const
{
	return state;
}

void acp::Connection::setState(NetworkState state)
{
	this->state = state;

	if (state == NetworkState::STATUS)
		networkHandler = std::make_unique<StatusHandler>(this);
	else if (state == NetworkState::LOGIN)
		networkHandler = std::make_unique<LoginHandler>(this);
	else if (state == NetworkState::CONFIGURATION)
		networkHandler = std::make_unique<ConfigurationHandler>(this);
	else if (state == NetworkState::PLAY)
		networkHandler = std::make_unique<PlayHandler>(this);
}

const acp::ProtocolVersion* acp::Connection::getProtocolVersion() const
{
	return protocolVersion;
}


std::string acp::Connection::toString(NetworkSide dest) const
{
	return std::format("{} {} {} [{}]",
					   clientSocket.getAddrStr(),
					   dest == NetworkSide::DEST ? "->" : "<-",
					   destSocket.getAddrStr(),
					   EnumNames<NetworkState>::get(state)
	);
}


bool acp::Connection::operator==(const Connection& rhs) const
{
	return clientSocket == rhs.clientSocket && destSocket == rhs.destSocket;
}

bool acp::Connection::operator!=(const Connection& rhs) const
{
	return !(*this == rhs);
}
