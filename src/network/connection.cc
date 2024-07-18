#include "connection.hh"

#include "handler/configuration_handler.hh"
#include "handler/login_handler.hh"
#include "handler/play_handler.hh"
#include "handler/status_handler.hh"
#include "protocol/packet/i_packet.hh"

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

	ByteBuf ogBuf = from.read();

	ByteBuf buf = ogBuf;
	bool rewrite = false;

	if (compressionThreshold.has_value())
	{
		const int dataLen = buf.readVarint();
		if (dataLen)
			buf = buf.decompress(dataLen);
	}

	const int id = buf.readVarint();
	std::unique_ptr<packet::IPacket> packet = protocolVersion == nullptr
												  ? std::make_unique<packet::handshake::Handshake>(buf)
												  : protocolVersion->getMapping().create(state, fromSide, id, buf);

	if (packet)
	{
		packet->read(protocolVersion);
		std::cout << std::format("[{}] {} -> {}: {}\n",
								 EnumNames<NetworkState>::get(state),
								 EnumNames<NetworkSide>::get(fromSide),
								 EnumNames<NetworkSide>::get(toSide),
								 packet->toString()
		);
		rewrite = packet->apply(networkHandler);
		if (rewrite)
			packet->write(protocolVersion);
	}
	else
	{
		std::cout << std::format("[{}] {} -> {}: packetId={}\n",
								 EnumNames<NetworkState>::get(state),
								 EnumNames<NetworkSide>::get(fromSide),
								 EnumNames<NetworkSide>::get(toSide),
								 id
		);
	}

	const ByteBuf& toWrite = rewrite ? packet->getBuf() : ogBuf;
	to.write(toWrite);

	// std::cout << std::format("[{}]: sent {}\n", toString(toSide), toWrite.toString());
}

acp::PlayerSocket& acp::Connection::getSide(NetworkSide side)
{
	return side == NetworkSide::CLIENT ? clientSocket : destSocket;
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

void acp::Connection::setProtocolVersion(const ProtocolVersion* protocol_version)
{
	protocolVersion = protocol_version;
}

void acp::Connection::setCompressionThreshold(int threshold)
{
	compressionThreshold = threshold;
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
