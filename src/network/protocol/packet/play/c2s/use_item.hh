#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class UseItem : public IPacket
	{
		/**
		 * - 0: main
		 * - 1: off
		 */
		int hand;
		/// 1.19 - now
		std::optional<int> sequence;
		/// 1.21 - now
		std::optional<float> yaw, pitch;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getHand() const;
		void setHand(int hand);

		std::optional<int> getSequence() const;
		void setSequence(const std::optional<int>& sequence);

		std::optional<float> getYaw() const;
		void setYaw(const std::optional<float>& yaw);

		std::optional<float> getPitch() const;
		void setPitch(const std::optional<float>& pitch);

		std::string toString() const override;
	};
}
