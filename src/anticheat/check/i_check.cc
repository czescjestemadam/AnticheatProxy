#include "i_check.hh"

#include "check_manager.hh"

acp::ICheck::ICheck(CheckManager* checkManager) : checkManager(checkManager)
{
}

void acp::ICheck::fail()
{
	failCount++;
	checkManager->fail(this);
}

void acp::ICheck::alert(const std::string& info)
{
	checkManager->alert(this, info);
}

int acp::ICheck::getFailCount() const
{
	return failCount;
}
