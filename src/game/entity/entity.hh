#pragma once
#include "entity_type.hh"
#include "util/uuid.hh"
#include "util/vec3.hh"

namespace acp::game
{
	class Entity
	{
	protected:
		int id;
		UUID uuid;
		EntityType type;
		Vec3d position;
		float yaw, pitch;
		bool onGround;

	public:
		Entity(int id, const UUID& uuid, EntityType type, const Vec3d& position, float yaw, float pitch);
		virtual ~Entity() = default;

		int getId() const;

		const UUID& getUuid() const;
		void setUuid(const UUID& uuid);

		EntityType getType() const;

		Vec3d& getPosition();
		const Vec3d& getPosition() const;
		void setPosition(const Vec3d& position);

		float getYaw() const;
		void setYaw(float yaw);

		float getPitch() const;
		void setPitch(float pitch);

		bool isOnGround() const;
		void setOnGround(bool on_ground);

		virtual std::string toString();
	};
}
