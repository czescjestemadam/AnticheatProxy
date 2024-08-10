#pragma once
#include "entity.hh"

namespace acp::game
{
	class LivingEntity : public Entity
	{
	protected:
		float headYaw;
		double health;

	public:
		LivingEntity(int id, const UUID& uuid, const EntityType* type, const Vec3d& position, float yaw, float pitch, bool onGround, float headYaw, double health);

		float getHeadYaw() const;
		void setHeadYaw(float head_yaw);

		double getHealth() const;
		void setHealth(double health);

		virtual Vec3d getEyePosition(const ProtocolVersion* version) const;
		Vec3d getDirection() const;

		BoundingBoxD getBoundingBox(const ProtocolVersion* version) const override;

		std::string toString() override;
	};
}
