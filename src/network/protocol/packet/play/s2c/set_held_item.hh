#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class SetHeldItem : public IPacket
	{
		byte_t slot;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		byte_t getSlot() const;
		void setSlot(byte_t slot);

		std::string toString() const override;
	};
}
