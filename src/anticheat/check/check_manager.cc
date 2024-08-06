#include "check_manager.hh"

acp::CheckManager::CheckManager(AcpPlayer* player) : player(player)
{

}

void acp::CheckManager::fail(ICheck* check)
{

}

acp::AcpPlayer* acp::CheckManager::getPlayer() const
{
	return player;
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
	return checks.contains(name) ? checks[name].get() :  nullptr;
}
