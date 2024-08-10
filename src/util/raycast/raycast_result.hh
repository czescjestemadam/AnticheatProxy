#pragma once
#include "util/box_face.hh"
#include "util/enum_names.hh"
#include "util/vec3.hh"

namespace acp
{
	struct RaycastResult
	{
		enum class Type
		{
			BLOCK,
			ENTITY
		};

		Vec3d hitPosition;

		explicit RaycastResult(const Vec3d& hit_position);
		virtual ~RaycastResult() = default;

		virtual Type getType() const = 0;
	};

	struct RaycastBlockResult : RaycastResult
	{
		Vec3i blockPos;
		BoxFace face;

		RaycastBlockResult(const Vec3d& hit_position, const Vec3i& block_pos, BoxFace face);

		Type getType() const override;
	};

	struct RaycastEntityResult : RaycastResult
	{
		int entityId;

		RaycastEntityResult(const Vec3d& hit_position, int entity_id);

		Type getType() const override;
	};

	template<>
	struct EnumNames<RaycastResult::Type>
	{
		static std::string get(RaycastResult::Type val);
	};
}
