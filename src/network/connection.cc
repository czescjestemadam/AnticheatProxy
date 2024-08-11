#include "connection.hh"

#include "anticheat_proxy.hh"
#include "handler/configuration_handler.hh"
#include "handler/login_handler.hh"
#include "handler/play_handler.hh"
#include "handler/status_handler.hh"
#include "protocol/packet/i_packet.hh"
#include "util/profiler/profiler.hh"
#include "util/text/translatable_component.hh"

acp::Connection::Connection(PlayerSocket&& clientSocket, PlayerSocket&& destSocket)
	: logger(SubLogger::fromRoot("Connection " + clientSocket.getAddrStr())),
	  clientSocket(std::move(clientSocket)),
	  destSocket(std::move(destSocket))

{
}

void acp::Connection::close(const std::unique_ptr<text::Component>& reason)
{
	if (clientSocket.isValid())
	{
		if (reason == nullptr)
			networkHandler->disconnect(std::make_unique<text::TranslatableComponent>("disconnect.closed"));
		else
			networkHandler->disconnect(reason);
	}

	destSocket.close();
	clientSocket.close();
}

void acp::Connection::handleEvent(int fd)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("Connection::handleEvent()");

	const NetworkSide fromSide = fd == clientSocket.getFd() ? NetworkSide::CLIENT : NetworkSide::DEST;
	const NetworkSide toSide = getOppositeSide(fromSide);
	PlayerSocket& from = getSide(fromSide);
	PlayerSocket& to = getSide(toSide);

	const ByteBuf ogBuf = from.read();

	ByteBuf buf = ogBuf;

	if (compressionThreshold.has_value())
	{
		const int dataLen = buf.readVarint();
		if (dataLen)
			buf = buf.decompress(dataLen);
	}

	const int id = buf.readVarint();
	std::unique_ptr<packet::IPacket> packet = protocolVersion == nullptr
												  ? std::make_unique<packet::handshake::Handshake>(buf)
												  : protocolVersion->getProtocolMapping().create(state, fromSide, id, buf);

	if (!packet)
	{
		sendPacket(toSide, id, buf);
		return;
	}

	try
	{
		packet->read(protocolVersion);
	}
	catch (const std::exception& ex)
	{
		logger.error("[{}] {} -> {}: error reading {}: {}",
					 EnumNames<NetworkState>::get(state),
					 EnumNames<NetworkSide>::get(fromSide),
					 EnumNames<NetworkSide>::get(toSide),
					 packet->toString(),
					 ex.what()
		);
		to.write(ogBuf);
		packetCount[toSide]++;
		return;
	}

	HandleResult result;
	try
	{
		result = packet->apply(networkHandler);
	}
	catch (const std::exception& ex)
	{
		logger.error("[{}] {} -> {}: error handling {}: {}",
					 EnumNames<NetworkState>::get(state),
					 EnumNames<NetworkSide>::get(fromSide),
					 EnumNames<NetworkSide>::get(toSide),
					 packet->toString(),
					 ex.what()
		);
		to.write(ogBuf);
		packetCount[toSide]++;
		return;
	}

	if (result == HandleResult::FORWARD)
	{
		// sendPacket(toSide, std::move(packet)); // strict read/write TODO fix some packets
		to.write(ogBuf);
		packetCount[toSide]++;
	}
	else if (result == HandleResult::REWRITE)
		sendPacket(toSide, std::move(packet));

	// logger.debug("[{}] {} -> {}: {} {}",
	// 			 EnumNames<NetworkState>::get(state),
	// 			 EnumNames<NetworkSide>::get(fromSide),
	// 			 EnumNames<NetworkSide>::get(toSide),
	// 			 EnumNames<HandleResult>::get(result),
	// 			 packet->toString()
	// );
}

void acp::Connection::sendPacket(NetworkSide to, std::unique_ptr<packet::IPacket>&& packet, bool write)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("Connection::sendPacket(to, packet, write)");

	if (!getSide(to).isValid())
		return;

	if (write)
		packet->write(protocolVersion);

	sendPacket(to, packet->getId(protocolVersion), packet->getBuf());
}

void acp::Connection::sendPacket(NetworkSide to, int packetId, const ByteBuf& packetData)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("Connection::sendPacket(to, pId, pData)");

	ByteBuf data;
	data.writeVarint(packetId);
	data.writeBuf(packetData);

	sendPacket(to, std::move(data));
}

void acp::Connection::sendPacket(NetworkSide to, ByteBuf&& data)
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("Connection::sendPacket(to, data)");

	if (compressionThreshold.has_value())
	{
		ByteBuf buf;

		const int dataLen = static_cast<int>(data.size());
		const int outCompressionThreshold = to == NetworkSide::DEST
												? AnticheatProxy::get()->getConfigManager().getNetwork().destinationOutCompressionThreshold
												: compressionThreshold.value();
		const bool compress = outCompressionThreshold < 0 ? false : dataLen >= outCompressionThreshold;

		buf.writeVarint(compress ? dataLen : 0);
		buf.writeBuf(compress ? data.compress() : data);

		getSide(to).write(buf);
	}
	else // before SetCompression packet
	{
		getSide(to).write(data);
	}

	packetCount[to]++;
}

acp::SubLogger& acp::Connection::getLogger()
{
	return logger;
}

acp::PlayerSocket& acp::Connection::getSide(NetworkSide side)
{
	return side == NetworkSide::CLIENT ? clientSocket : destSocket;
}

size_t acp::Connection::getPacketCount(NetworkSide to) const
{
	return packetCount.at(to);
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

acp::GameProfile& acp::Connection::getGameProfile()
{
	return gameProfile;
}

void acp::Connection::setGameProfile(const GameProfile& game_profile)
{
	gameProfile = game_profile;
}

const std::vector<std::unique_ptr<acp::nbt::Tag>>& acp::Connection::getDamageTypes() const
{
	return damageTypes;
}

std::vector<std::unique_ptr<acp::nbt::Tag>>& acp::Connection::getDamageTypes()
{
	return damageTypes;
}

std::vector<acp::registry::DimensionTypeEntry>& acp::Connection::getDimensionTypes()
{
	return dimensionTypes;
}

const std::vector<acp::registry::DimensionTypeEntry>& acp::Connection::getDimensionTypes() const
{
	return dimensionTypes;
}

acp::AcpPlayer& acp::Connection::getPlayer()
{
	return player;
}

void acp::Connection::setPlayer(AcpPlayer&& player)
{
	this->player = std::move(player);
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
