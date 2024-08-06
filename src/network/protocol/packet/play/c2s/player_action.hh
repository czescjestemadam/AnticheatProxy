#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	/// block mining
	class PlayerAction : public IPacket
	{
		int status;
		Vec3i blockPosition;
		byte_t face;
		/// 1.19 - now
		std::optional<int> sequence;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getStatus() const;
		void setStatus(int status);

		Vec3i getBlockPosition() const;
		void setBlockPosition(const Vec3i& block_position);

		byte_t getFace() const;
		void setFace(byte_t face);

		const std::optional<int>& getSequence() const;
		void setSequence(const std::optional<int>& sequence);

		std::string toString() const override;
	};
}
