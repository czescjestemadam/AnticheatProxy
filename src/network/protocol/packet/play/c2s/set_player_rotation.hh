#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::c2s
{
	class SetPlayerRotation : public IPacket
	{
		float yaw, pitch;
		bool onGround;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		float getYaw() const;
		void setYaw(float yaw);

		float getPitch() const;
		void setPitch(float pitch);

		bool isOnGround() const;
		void setOnGround(bool on_ground);

		std::string toString() const override;
	};
}
