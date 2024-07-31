#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::configuration::c2s
{
	class KnownPacks : public IPacket
	{
		std::vector<std::array<std::string, 3>> packs;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::vector<std::array<std::string, 3>>& getPacks();
		void setPacks(const std::vector<std::array<std::string, 3>>& packs);

		std::string toString() const override;
	};
}
