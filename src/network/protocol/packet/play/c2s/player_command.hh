#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class PlayerCommand : public IPacket
	{
		int entityId;

		/// enum
		/// - 0: start sneaking
		/// - 1: stop sneaking
		/// - 2: leave bed
		/// - 3: start sprinting
		/// - 4: stop sprinting
		/// - 5: start horse jump
		/// - 6: stop horse jump
		/// - 7: open vehicle inventory
		/// - 8: start elytra fly
		int action;
		int jumpBoost;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getEntityId() const;
		void setEntityId(int entity_id);

		int getAction() const;
		void setAction(int action);

		int getJumpBoost() const;
		void setJumpBoost(int jump_boost);

		std::string toString() const override;
	};
}
