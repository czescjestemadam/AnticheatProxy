#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class SetCooldown : public IPacket
	{
		int itemId;
		int ticks;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getItemId() const;
		void setItemId(int item_id);

		int getTicks() const;
		void setTicks(int ticks);

		std::string toString() const override;
	};
}
