#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class PlayerAbilities : public IPacket
	{
		/// 0x02 - flying
		byte_t flags;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		byte_t getFlags() const;
		void setFlags(byte_t flags);

		std::string toString() const override;
	};
}
