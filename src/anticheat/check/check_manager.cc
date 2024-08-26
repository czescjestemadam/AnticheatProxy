#include "check_manager.hh"

#include "anticheat_proxy.hh"
#include "interact/reach.hh"

acp::CheckManager::CheckManager(Connection* connection) : connection(connection)
{
	if (!connection)
		return;

	addCheck<check::Reach>();
}

acp::Connection* acp::CheckManager::getConnection() const
{
	return connection;
}

bool acp::CheckManager::isExempt() const
{
	return exempt;
}

void acp::CheckManager::setExempt(const bool exempt)
{
	this->exempt = exempt;
}

std::unordered_map<std::string, std::unique_ptr<acp::ICheck>>& acp::CheckManager::getChecks()
{
	return checks;
}

const std::unordered_map<std::string, std::unique_ptr<acp::ICheck>>& acp::CheckManager::getChecks() const
{
	return checks;
}

acp::ICheck* acp::CheckManager::getByName(const std::string& name)
{
	return checks.contains(name) ? checks[name].get() : nullptr;
}
