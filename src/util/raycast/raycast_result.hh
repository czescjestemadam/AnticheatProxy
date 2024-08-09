#pragma once
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

		virtual ~RaycastResult() = default;

		virtual Type getType() const = 0;
	};

	struct RaycastBlockResult : RaycastResult
	{
		Vec3i blockPos;
		// TODO block face

		Type getType() const override;
	};

	struct RaycastEntityResult : RaycastResult
	{
		int entityId;

		Type getType() const override;
	};

	template<>
	struct EnumNames<RaycastResult::Type>
	{
		static std::string get(RaycastResult::Type val);
	};
}
