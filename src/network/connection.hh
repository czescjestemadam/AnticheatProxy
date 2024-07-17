#pragma once
#include "protocol/network_state.hh"
#include "protocol/protocol_version.hh"
#include "socket/player_socket.hh"
#include "handler/i_network_handler.hh"
#include "handler/handshake_handler.hh"

#include <optional>
#include <memory>

namespace acp
{
	class Connection
	{
		PlayerSocket clientSocket;
		PlayerSocket destSocket;

		std::unique_ptr<INetworkHandler> networkHandler = std::make_unique<HandshakeHandler>(this);

		NetworkState state = NetworkState::HANDSHAKE;
		const ProtocolVersion* protocolVersion = nullptr;
		std::optional<int> compressionThreshold;

	public:
		Connection(PlayerSocket&& clientSocket, PlayerSocket&& destSocket);
		Connection(Connection&&) = default;

		void close();

		void handleEvent(int fd);

		// TODO packets

		PlayerSocket& getSide(NetworkSide side);

		NetworkState getState() const;
		void setState(NetworkState state);

		const ProtocolVersion* getProtocolVersion() const;
		void setCompressionThreshold(int threshold);

		std::string toString(NetworkSide dest = NetworkSide::DEST) const;

		bool operator==(const Connection& rhs) const;
		bool operator!=(const Connection& rhs) const;
	};
}
