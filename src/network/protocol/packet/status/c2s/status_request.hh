#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::status::c2s
{
	class StatusRequest : public IPacket
	{
	public:
		using IPacket::IPacket;

		void read() override;
		void write() override;

		std::string toString() const override;
	};
}
