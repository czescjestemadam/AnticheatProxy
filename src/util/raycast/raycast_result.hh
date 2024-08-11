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

		/// v < 0 means ray startPos was inside BoundingBox
		double hitDistanceMin;
		double hitDistanceMax;
		Vec3d hitPositionMin;
		Vec3d hitPositionMax;

		virtual ~RaycastResult() = default;

		virtual Type getType() const = 0;
	};

	struct RaycastBlockResult : RaycastResult
	{
		Vec3i blockPos;
		BoxFace face;

		RaycastBlockResult(const Vec3i& block_pos, BoxFace face);

		Type getType() const override;
	};

	struct RaycastEntityResult : RaycastResult
	{
		int entityId;

		RaycastEntityResult(int entity_id);

		Type getType() const override;
	};

	template<>
	struct EnumNames<RaycastResult::Type>
	{
		static std::string get(RaycastResult::Type val);
	};
}
