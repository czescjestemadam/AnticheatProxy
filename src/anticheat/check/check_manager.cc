#include "check_manager.hh"

acp::CheckManager::CheckManager()
{

}

acp::ICheck* acp::CheckManager::getByName(const std::string& name)
{
	return checks.contains(name) ? checks[name].get() :  nullptr;
}
