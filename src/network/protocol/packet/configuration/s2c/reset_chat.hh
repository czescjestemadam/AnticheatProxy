#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::configuration::s2c
{
	class ResetChat : public IPacket
	{
	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		std::string toString() const override;
	};
}
