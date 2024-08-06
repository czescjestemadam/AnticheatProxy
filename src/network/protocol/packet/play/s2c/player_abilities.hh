#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class PlayerAbilities : public IPacket
	{
		byte_t flags;
		float flyingSpeed;
		/// same as walk speed from @c UpdateAttributes
		float fovModifier;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		HandleResult apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		byte_t getFlags() const;
		void setFlags(byte_t flags);

		float getFlyingSpeed() const;
		void setFlyingSpeed(float flying_speed);

		float getFovModifier() const;
		void setFovModifier(float fov_modifier);

		std::string toString() const override;
	};
}
