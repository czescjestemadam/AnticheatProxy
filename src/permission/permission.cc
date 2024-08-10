#include "permission.hh"

#include <unordered_map>

static std::unordered_map<std::string, acp::Permission*> permissionByName;

acp::Permission::Permission(int idx, const std::string& name) : idx(idx), name(name)
{
	permissionByName[name] = this;
}

const std::string& acp::Permission::getName() const
{
	return name;
}

bool acp::Permission::operator==(const Permission& rhs) const
{
	return idx == rhs.idx;
}

bool acp::Permission::operator!=(const Permission& rhs) const
{
	return !(*this == rhs);
}


acp::Permission* acp::Permission::getByName(const std::string& name)
{
	return permissionByName.contains(name) ? permissionByName[name] : nullptr;
}

const acp::Permission acp::Permission::ALERT = { 0, "acp.alert" };
const acp::Permission acp::Permission::CMD = { 1, "acp.cmd" };
const acp::Permission acp::Permission::CMD_IP = { 1, "acp.cmd.ip" };
const acp::Permission acp::Permission::CMD_ADMIN = { 1, "acp.cmd.admin" };
const acp::Permission acp::Permission::PROFILE = { 2, "acp.profile" };
const acp::Permission acp::Permission::LOGS = { 3, "acp.logs" };
const acp::Permission acp::Permission::EXEMPT = { 4, "acp.exempt" };
