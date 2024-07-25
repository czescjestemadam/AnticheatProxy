#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class SetPlayerOnGround : public IPacket
	{
		bool onGround;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		bool isOnGround() const;
		void setOnGround(bool on_ground);

		std::string toString() const override;
	};
}
