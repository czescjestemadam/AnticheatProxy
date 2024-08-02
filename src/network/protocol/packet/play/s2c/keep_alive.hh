#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class KeepAlive : public IPacket
	{
		long keepAliveId;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		long getKeepAliveId() const;
		void setKeepAliveId(long keep_alive_id);

		std::string toString() const override;
	};
}
