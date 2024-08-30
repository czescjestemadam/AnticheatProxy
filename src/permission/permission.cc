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

static int IDX_COUNTER = 0;

const acp::Permission acp::Permission::ALERT = { IDX_COUNTER++, "acp.alert" };
const acp::Permission acp::Permission::CMD = { IDX_COUNTER++, "acp.cmd" };
const acp::Permission acp::Permission::CMD_IP = { IDX_COUNTER++, "acp.cmd.ip" };
const acp::Permission acp::Permission::CMD_ADMIN = { IDX_COUNTER++, "acp.cmd.admin" };
const acp::Permission acp::Permission::PROFILE = { IDX_COUNTER++, "acp.profile" };
const acp::Permission acp::Permission::LOGS = { IDX_COUNTER++, "acp.logs" };
const acp::Permission acp::Permission::EXEMPT = { IDX_COUNTER++, "acp.exempt" };
const acp::Permission acp::Permission::RELOAD = { IDX_COUNTER++, "acp.reload" };
const acp::Permission acp::Permission::STOP = { IDX_COUNTER++, "acp.stop" };
