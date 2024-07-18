#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::configuration::s2c
{
	class FeatureFlags : public IPacket
	{
		std::vector<Identifier> flags;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::vector<Identifier>& getFlags();
		void setFlags(const std::vector<Identifier>& flags);

		std::string toString() const override;
	};
}
