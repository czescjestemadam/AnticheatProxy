#pragma once
#include "permission.hh"

#include <unordered_map>
#include <vector>

#include "util/logger/sub_logger.hh"

namespace acp
{
	class PermissionManager
	{
		SubLogger logger = SubLogger::fromRoot("PermissionManager");
		std::unordered_map<std::string, std::vector<const Permission*>> permissionsByUsername;

	public:
		PermissionManager();

		void load();

		std::vector<const Permission*> getFor(const std::string& username) const;
		bool hasPermission(const std::string& username, const Permission& permission) const;
	};
}
