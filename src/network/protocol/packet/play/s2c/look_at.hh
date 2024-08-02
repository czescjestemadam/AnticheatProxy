#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class LookAt : public IPacket
	{
		/// enum
		/// - @c 0: feet
		/// - @c 1: eyes
		int feetEyes;
		Vec3d target;
		bool isEntity;
		std::optional<std::pair<int, int>> entityIdFeetEyes;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getFeetEyes() const;
		void setFeetEyes(int feet_eyes);

		const Vec3d& getTarget() const;
		void setTarget(const Vec3d& target);

		bool isIsEntity() const;
		void setIsEntity(bool is_entity);

		const std::optional<std::pair<int, int>>& getEntityIdFeetEyes() const;
		void setEntityIdFeetEyes(const std::optional<std::pair<int, int>>& entity_id_feet_eyes);

		std::string toString() const override;
	};
}
