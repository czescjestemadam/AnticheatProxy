#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::configuration::c2s
{
	class Pong : public IPacket
	{
		int pongId;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getPongId() const;
		void setPongId(int pong_id);

		std::string toString() const override;
	};
}
