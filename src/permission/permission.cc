#include "permission.hh"

#include <map>

static std::map<std::string, Permission*> permissionByName;

Permission::Permission(int idx, const std::string& name) : idx(idx), name(name)
{
	permissionByName[name] = this;
}

const std::string& Permission::getName() const
{
	return name;
}

bool Permission::operator==(const Permission& rhs) const
{
	return idx == rhs.idx;
}

bool Permission::operator!=(const Permission& rhs) const
{
	return !(*this == rhs);
}


Permission* Permission::getByName(const std::string& name)
{
	return permissionByName[name];
}

static int idx = 0;

const Permission ALERT = { idx++, "acp.alert" };
const Permission CMD = { idx++, "acp.cmd" };
const Permission PROFILE = { idx++, "acp.profile" };
const Permission LOGS = { idx++, "acp.logs" };
const Permission EXEMPT = { idx++, "acp.exempt" };
