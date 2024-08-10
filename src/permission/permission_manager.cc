#include "permission_manager.hh"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

acp::PermissionManager::PermissionManager()
{
	load();
}

void acp::PermissionManager::load()
{
	const auto file = std::filesystem::current_path() / "permissions.json";
	if (!exists(file))
	{
		logger.warn("{} does not exist, generating example file", file.c_str());

		nlohmann::json j;
		j["nonek_"] = {
			Permission::CMD.getName(),
			Permission::CMD_ADMIN.getName(),
			Permission::EXEMPT.getName(),
		};

		std::ofstream ofs(file);
		if (!ofs.good())
			throw std::runtime_error("fstream::good() == false");

		ofs << j.dump(2);
		ofs.close();

		return;
	}

	std::ifstream ifs(file);
	if (!ifs.good())
		throw std::runtime_error("fstream::good() == false");

	nlohmann::json j = nlohmann::json::parse(ifs);
	for (const auto& [key, val] : j.items())
	{
		std::vector<const Permission*> permissions;
		for (auto& permissionName : val)
		{
			if (const Permission* permission = Permission::getByName(permissionName))
				permissions.push_back(permission);
		}

		permissionsByUsername[key] = std::move(permissions);
	}

	logger.info("Loaded permissions for {} players", j.size());
}

std::vector<const acp::Permission*> acp::PermissionManager::getFor(const std::string& username) const
{
	if (permissionsByUsername.contains(username))
		return permissionsByUsername.at(username);

	return {};
}

bool acp::PermissionManager::hasPermission(const std::string& username, const Permission& permission) const
{
	const auto& permissions = getFor(username);
	if (permissions.empty())
		return false;

	for (const Permission* perm : permissions)
	{
		if (*perm == permission)
			return true;
	}

	return false;
}
