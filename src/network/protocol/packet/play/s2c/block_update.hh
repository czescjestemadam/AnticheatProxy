#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class BlockUpdate : public IPacket
	{
		Vec3i blockPosition;
		int blockId;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		Vec3i getBlockPosition() const;
		void setBlockPosition(const Vec3i& block_position);

		int getBlockId() const;
		void setBlockId(int block_id);

		std::string toString() const override;
	};
}
