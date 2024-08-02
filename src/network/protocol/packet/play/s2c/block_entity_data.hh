#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class BlockEntityData : public IPacket
	{
		Vec3i position;
		/// Action field (pvn < 1.18):
		/// - @c 1: Set data of a mob spawner (everything except for SpawnPotentials: current delay, min/max delay, mob to be spawned, spawn count, spawn range, etc.)
		/// - @c 2: Set command block text (command and last execution status)
		/// - @c 3: Set the level, primary, and secondary powers of a beacon
		/// - @c 4: Set rotation and skin of mob head
		/// - @c 5: Declare a conduit
		/// - @c 6: Set base color and patterns on a banner
		/// - @c 7: Set the data for a Structure tile entity
		/// - @c 8: Set the destination for a end gateway
		/// - @c 9: Set the text on a sign
		/// - @c 10: Unused
		/// - @c 11: Declare a bed
		/// - @c 12: Set data of a jigsaw block
		/// - @c 13: Set items in a campfire
		/// - @c 14: Beehive information
		int type;
		std::unique_ptr<nbt::Tag> data;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		const Vec3i& getPosition() const;
		void setPosition(const Vec3i& position);

		int getType() const;
		void setType(int type);

		std::unique_ptr<nbt::Tag>& getData();
		const std::unique_ptr<nbt::Tag>& getData() const;
		void setData(std::unique_ptr<nbt::Tag>&& data);

		std::string toString() const override;
	};
}
