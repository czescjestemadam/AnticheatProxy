#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	/// prev name: @c Spectate
	class TeleportToEntity : public IPacket
	{
		UUID targetPlayer;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		const UUID& getTargetPlayer() const;
		void setTargetPlayer(const UUID& target_player);

		std::string toString() const override;
	};
}
