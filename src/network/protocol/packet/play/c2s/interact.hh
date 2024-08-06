#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class Interact : public IPacket
	{
		int entityId;
		/**
		 * - 0: interact
		 * - 1: attack
		 * - 2: interact at
		 */
		int type;
		/// type == 2
		std::optional<Vec3f> target;
		/// type == 0 || type == 2
		std::optional<int> hand;
		bool sneaking;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int& getEntityId();
		void setEntityId(int entity_id);

		int& getType();
		void setType(int type);

		const std::optional<Vec3f>& getTarget() const;
		void setTarget(const std::optional<Vec3f>& target);

		std::optional<int>& getHand();
		void setHand(const std::optional<int>& hand);

		bool& isSneaking();
		void setSneaking(bool sneaking);

		std::string toString() const override;
	};
}
