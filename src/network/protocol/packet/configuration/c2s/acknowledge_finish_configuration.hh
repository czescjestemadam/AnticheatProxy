#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::configuration::c2s
{
	class AcknowledgeFinishConfiguration : public IPacket
	{
	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::string toString() const override;
	};
}
