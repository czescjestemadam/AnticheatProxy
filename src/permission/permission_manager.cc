#include "permission_manager.hh"

void acp::PermissionManager::load()
{
}

const std::vector<Permission*> acp::PermissionManager::getFor(void* player)
{
	return {};
}

bool acp::PermissionManager::hasPermission(void* player, const Permission* permission)
{
	return true;
}
