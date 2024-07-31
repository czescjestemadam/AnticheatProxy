#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class SynchronizePlayerPosition : public IPacket
	{
		/// field absolute if flags == 0
		Vec3d position;
		/// field absolute if flags == 0
		float yaw, pitch;

		/// position flags
		/// - x: 0x01
		/// - y: 0x02
		/// - z: 0x04
		/// - pitch: 0x08
		/// - yaw: 0x10
		byte_t flags;

		int teleportId;

		/// 1.17 - 1.19.3
		std::optional<bool> dismount;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		Vec3d& getPosition();
		void setPosition(const Vec3d& position);

		float getYaw() const;
		void setYaw(float yaw);

		float getPitch() const;
		void setPitch(float pitch);

		byte_t getFlags() const;
		void setFlags(byte_t flags);

		int getTeleportId() const;
		void setTeleportId(int teleport_id);

		std::optional<bool>& getDismount();
		void setDismount(const std::optional<bool>& dismount);

		std::string toString() const override;
	};
}
