#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class SpawnEntity : public IPacket
	{
		int entityId;
		UUID entityUuid;
		int type;
		Vec3d position;
		float pitch, yaw;
		/// 1.19 - now
		std::optional<float> headYaw;
		int data;
		Vec3s velocity;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getEntityId() const;
		void setEntityId(int entity_id);

		UUID getEntityUuid() const;
		void setEntityUuid(const UUID& entity_uuid);

		int getType() const;
		void setType(int type);

		Vec3d getPosition() const;
		void setPosition(const Vec3d& position);

		float getPitch() const;
		void setPitch(float pitch);

		float getYaw() const;
		void setYaw(float yaw);

		const std::optional<float>& getHeadYaw() const;
		void setHeadYaw(const std::optional<float>& head_yaw);

		int getData() const;
		void setData(int data);

		Vec3s getVelocity() const;
		void setVelocity(const Vec3s& velocity);

		std::string toString() const override;
	};
}
