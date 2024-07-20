#pragma once
#include "network/protocol/packet/i_packet.hh"

namespace acp::packet::play::s2c
{
	class SetHealth : public IPacket
	{
		float health;
		int food;
		float foodSaturation;

	public:
		using IPacket::IPacket;

		void read(const ProtocolVersion* version) override;
		void write(const ProtocolVersion* version) override;

		bool apply(std::unique_ptr<INetworkHandler>& handler) override;

		int getId(const ProtocolVersion* version) const override;

		float getHealth() const;
		void setHealth(float health);

		int getFood() const;
		void setFood(int food);

		float getFoodSaturation() const;
		void setFoodSaturation(float food_saturation);

		std::string toString() const override;
	};
}
