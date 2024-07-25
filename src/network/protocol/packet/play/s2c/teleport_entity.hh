#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class TeleportEntity : public IPacket
	{
		int entityId;
		Vec3d position;
		/// not delta
		float yaw, pitch;
		bool onGround;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		int getEntityId() const;
		void setEntityId(int entity_id);

		Vec3d getPosition() const;
		void setPosition(const Vec3d& position);

		float getYaw() const;
		void setYaw(float yaw);

		float getPitch() const;
		void setPitch(float pitch);

		bool isOnGround() const;
		void setOnGround(bool on_ground);

		std::string toString() const override;
	};
}
