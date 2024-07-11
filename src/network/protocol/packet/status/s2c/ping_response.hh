#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::status::s2c
{
	class PingResponse : public IPacket
	{
		long timestamp;

	public:
		using IPacket::IPacket;

		void read() override;
		void write() override;

		long getTimestamp() const;
		void setTimestamp(long timestamp);

		std::string toString() const override;
	};
}
