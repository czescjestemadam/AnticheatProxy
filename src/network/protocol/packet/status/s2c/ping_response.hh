#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::status::s2c
{
	class PingResponse : public IPacket
	{
		long timestamp;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		long getTimestamp() const;
		void setTimestamp(long timestamp);

		std::string toString() const override;
	};
}
