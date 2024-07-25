#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class OpenSignEditor : public IPacket
	{
		Vec3i blockPosition;
		/// 1.20 - now
		std::optional<bool> front;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		Vec3i& getBlockPosition();
		const Vec3i& getBlockPosition() const;
		void setBlockPosition(const Vec3i& block_position);

		std::optional<bool> getFront() const;
		void setFront(const std::optional<bool>& front);

		std::string toString() const override;
	};
}
