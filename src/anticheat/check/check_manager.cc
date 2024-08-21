#include "check_manager.hh"

#include "anticheat_proxy.hh"
#include "anticheat/acp_player.hh"
#include "anticheat/alert/alert.hh"

acp::CheckManager::CheckManager(AcpPlayer* player) : player(player)
{

}

void acp::CheckManager::fail(ICheck* check)
{

}

void acp::CheckManager::alert(const ICheck* check, const std::string& info)
{
	const Alert alert(player->getProfile().username, check->toString(), info, check->getFailCount());
	AnticheatProxy::get()->getAlertManager().send(alert);
}

acp::AcpPlayer* acp::CheckManager::getPlayer() const
{
	return player;
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
	return checks.contains(name) ? checks[name].get() :  nullptr;
}
