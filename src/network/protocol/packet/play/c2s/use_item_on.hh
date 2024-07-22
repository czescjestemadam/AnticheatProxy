#pragma once
#include "network/protocol/packet/i_packet.hh"
#include "util/vec3.hh"

namespace acp::packet::play::c2s
{
	class UseItemOn : public IPacket
	{
		/**
		 * - 0: main
		 * - 1: off
		 */
		int hand;
		Vec3i blockPosition;
		int face;
		Vec3f cursorPosition;
		bool insideBlock;
		std::optional<int> sequence;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getHand() const;
		void setHand(int hand);

		Vec3i getBlockPosition() const;
		void setBlockPosition(const Vec3i& block_position);

		int getFace() const;
		void setFace(int face);

		Vec3f getCursorPosition() const;
		void setCursorPosition(const Vec3f& cursor_position);

		bool isInsideBlock() const;
		void setInsideBlock(bool inside_block);

		std::optional<int> getSequence() const;
		void setSequence(const std::optional<int>& sequence);

		std::string toString() const override;
	};
}
