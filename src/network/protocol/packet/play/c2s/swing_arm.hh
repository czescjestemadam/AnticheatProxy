#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class SwingArm : public IPacket
	{
		/**
		 * - 0: main hand
		 * - 1: off hand
		 */
		int hand;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int& getHand();
		void setHand(int hand);

		std::string toString() const override;
	};
}
