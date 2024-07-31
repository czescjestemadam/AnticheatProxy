#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class UpdateSign : public IPacket
	{
		Vec3i blockPosition;
		/// 1.20 - now
		std::optional<bool> front;
		std::array<std::string, 4> lines;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		Vec3i& getBlockPosition();
		const Vec3i& getBlockPosition() const;
		void setBlockPosition(const Vec3i& block_position);

		std::optional<bool>& getFront();
		const std::optional<bool>& getFront() const;
		void setFront(const std::optional<bool>& front);

		std::array<std::string, 4>& getLines();
		const std::array<std::string, 4>& getLines() const;
		void setLines(const std::array<std::string, 4>& lines);

		std::string toString() const override;
	};
}
