#pragma once
#include "raycast_result.hh"

#include <memory>
#include <vector>

namespace acp
{
	struct RaycastingOptions
	{
		double distance = 6;
		bool blocks = true;
		bool includeFluids = false;
		bool entities = true;
		bool stopOnFirstResult = true;
	};

	class IRaycastable
	{
	public:
		virtual ~IRaycastable() = default;

		virtual std::vector<std::unique_ptr<RaycastResult>> raycast(const RaycastingOptions& options) const = 0;
	};
}
