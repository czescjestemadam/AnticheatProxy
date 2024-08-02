#pragma once
#include "util/uuid.hh"
#include "util/vec3.hh"

namespace acp::game
{
	class Entity
	{
	protected:
		int id;
		UUID uuid;
		// TODO type
		Vec3d position;
		float yaw, pitch;

	public:
		Entity(int id, const UUID& uuid, const Vec3d& position, float yaw, float pitch);
		virtual ~Entity() = default;

		int getId() const;
		void setId(int id);

		const UUID& getUuid() const;
		void setUuid(const UUID& uuid);

		const Vec3d& getPosition() const;
		void setPosition(const Vec3d& position);

		float getYaw() const;
		void setYaw(float yaw);

		float getPitch() const;
		void setPitch(float pitch);

		virtual std::string toString();
	};
}
