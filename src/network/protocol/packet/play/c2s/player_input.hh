#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class PlayerInput : public IPacket
	{
		float sideways;
		float forward;
		/// mask
		/// - @c 0x1: jump
		/// - @c 0x2: unmount
		byte_t flags;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;\

		float getSideways() const;
		void setSideways(float sideways);

		float getForward() const;
		void setForward(float forward);

		byte_t getFlags() const;
		void setFlags(byte_t flags);

		std::string toString() const override;
	};
}
