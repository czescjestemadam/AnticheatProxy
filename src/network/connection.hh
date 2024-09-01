#pragma once
#include "plugin_messenger.hh"
#include "protocol/network_state.hh"
#include "protocol/protocol_version.hh"
#include "socket/player_socket.hh"
#include "handler/i_network_handler.hh"
#include "handler/handshake_handler.hh"
#include "util/logger/sub_logger.hh"
#include "util/game_profile.hh"
#include "util/text/component.hh"
#include "anticheat/acp_player.hh"
#include "util/registry/dimension_type.hh"

#include <optional>
#include <memory>

namespace acp
{
	class Connection
	{
		SubLogger logger;

		PlayerSocket clientSocket;
		PlayerSocket destSocket;
		std::mutex clientSocketMx;
		std::mutex destSocketMx;

		std::unordered_map<NetworkSide, size_t> packetCount;

		std::unique_ptr<INetworkHandler> networkHandler = std::make_unique<HandshakeHandler>(this);

		NetworkState state = NetworkState::HANDSHAKE;
		const ProtocolVersion* protocolVersion = nullptr;
		std::optional<int> compressionThreshold;

		std::string clientbrand;
		PluginMessenger messenger;

		GameProfile gameProfile;
		std::vector<std::unique_ptr<nbt::Tag>> damageTypes;
		std::vector<registry::DimensionTypeEntry> dimensionTypes;
		AcpPlayer player;

	public:
		Connection(PlayerSocket&& clientSocket, PlayerSocket&& destSocket);
		Connection(Connection&&) = default;

		void close(const std::unique_ptr<text::Component>& reason);

		void handleEvent(int fd);

		void sendPacket(NetworkSide to, const std::unique_ptr<packet::IPacket>& packet, bool write = true);
		void sendPacket(NetworkSide to, int packetId, const ByteBuf& packetData);
		void sendPacket(NetworkSide to, ByteBuf&& data);

		SubLogger& getLogger();

		PlayerSocket& getSide(NetworkSide side);

		size_t getPacketCount(NetworkSide to) const;

		NetworkState getState() const;
		void setState(NetworkState state);

		const ProtocolVersion* getProtocolVersion() const;
		void setProtocolVersion(const ProtocolVersion* protocol_version);
		void setCompressionThreshold(int threshold);

		const std::string& getClientbrand() const;
		void setClientbrand(const std::string& clientbrand);

		PluginMessenger& getMessenger();
		const PluginMessenger& getMessenger() const;

		GameProfile& getGameProfile();
		void setGameProfile(const GameProfile& game_profile);

		std::vector<std::unique_ptr<nbt::Tag>>& getDamageTypes();
		const std::vector<std::unique_ptr<nbt::Tag>>& getDamageTypes() const;

		std::vector<registry::DimensionTypeEntry>& getDimensionTypes();
		const std::vector<registry::DimensionTypeEntry>& getDimensionTypes() const;

		AcpPlayer& getPlayer();
		void setPlayer(AcpPlayer&& player);

		std::string toString(NetworkSide dest = NetworkSide::DEST) const;

		bool operator==(const Connection& rhs) const;
		bool operator!=(const Connection& rhs) const;
	};
}
