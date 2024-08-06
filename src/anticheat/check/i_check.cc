#include "i_check.hh"

#include "check_manager.hh"

acp::ICheck::ICheck(CheckManager* checkManager) : checkManager(checkManager)
{
}

void acp::ICheck::fail()
{
	checkManager->fail(this);
}
