#pragma once
#include "network/protocol/protocol_version.hh"
#include "type/entity_type.hh"
#include "util/bounding_box.hh"
#include "util/uuid.hh"
#include "util/vec3.hh"

namespace acp::game
{
	class Entity
	{
	protected:
		int id;
		UUID uuid;
		const EntityType* type;
		Vec3d position;
		float yaw, pitch;
		bool onGround;

	public:
		Entity(int id, const UUID& uuid, const EntityType* type, const Vec3d& position, float yaw, float pitch, bool onGround);
		virtual ~Entity() = default;

		int getId() const;

		const UUID& getUuid() const;
		void setUuid(const UUID& uuid);

		const EntityType* getType() const;

		virtual BoundingBoxD getBoundingBox(const ProtocolVersion* version) const;

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
