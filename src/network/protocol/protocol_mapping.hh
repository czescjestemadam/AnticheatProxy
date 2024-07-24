#pragma once
#include "packet/i_packet.hh"
#include "network_state.hh"
#include "network/network_side.hh"

#include <functional>
#include <unordered_map>
#include <memory>

namespace acp
{
	class ProtocolMapping
	{
		using PacketConstructor = std::function<std::unique_ptr<packet::IPacket>(const ByteBuf&)>;
		using PacketIdMap = std::unordered_map<int, PacketConstructor>;

		std::unordered_map<NetworkState, std::unordered_map<NetworkSide, PacketIdMap>> mappings;

	public:
		ProtocolMapping() = default;
		explicit ProtocolMapping(const ProtocolVersion* version);

		std::unique_ptr<packet::IPacket> create(NetworkState state, NetworkSide sourceSide, int id, const ByteBuf& buf) const;

		size_t size() const;
	};
}
