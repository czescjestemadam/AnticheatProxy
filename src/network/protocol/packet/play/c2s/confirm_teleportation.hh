#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class ConfirmTeleportation : public IPacket
	{
		/// id from SynchronizePlayerPosition
		int teleportId;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getTeleportId() const;
		void setTeleportId(int teleport_id);

		std::string toString() const override;
	};
}
