#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::status::c2s
{
	class PingRequest : public IPacket
	{
		long timestamp;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		long getTimestamp() const;
		void setTimestamp(long timestamp);

		std::string toString() const override;
	};
}
