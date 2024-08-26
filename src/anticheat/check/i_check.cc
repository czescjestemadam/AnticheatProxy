#include "i_check.hh"

#include "anticheat_proxy.hh"

acp::ICheck::ICheck(Connection* connection) : connection(connection)
{
}

void acp::ICheck::fail(bool sendAlert, const std::string& info)
{
	failCount++;
	if (sendAlert)
		AnticheatProxy::get()->getAlertManager().send({ connection->getGameProfile().username, getName(), info, getDescription(), failCount });
}

int acp::ICheck::getCount() const
{
	return count;
}

int acp::ICheck::getFailCount() const
{
	return failCount;
}
