#pragma once
#include "entity.hh"

namespace acp::game
{
	class LivingEntity : public Entity
	{
	protected:
		double health;

	public:
		LivingEntity(int id, const UUID& uuid, const EntityType* type, const Vec3d& position, float yaw, float pitch, bool onGround, double health);

		double getHealth() const;
		void setHealth(double health);

		std::string toString() override;
	};
}
