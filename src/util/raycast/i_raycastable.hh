#pragma once
#include "raycast_result.hh"

#include <memory>
#include <vector>

namespace acp
{
	class IRaycastable
	{
	public:
		virtual ~IRaycastable() = default;

		virtual std::vector<std::unique_ptr<RaycastResult>> raycast(
			double distance,
			const std::vector<RaycastResult::Type>& types,
			bool includeFluids
		) const = 0;
	};
}
