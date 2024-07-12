#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::status::c2s
{
	class StatusRequest : public IPacket
	{
	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		int getId(const ProtocolVersion* version) const override;

		std::string toString() const override;
	};
}
