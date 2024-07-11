#pragma once
#include "permission.hh"

#include <vector>

namespace acp
{
	class PermissionManager
	{
	public:
		void load();

		const std::vector<Permission*> getFor(void* player);
		bool hasPermission(void* player, const Permission* permission);
	};
}
