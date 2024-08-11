#include "i_command.hh"

acp::ICommand::ICommand(const Permission* permission): permission(permission)
{
}

const acp::Permission* acp::ICommand::getPermission() const
{
	return permission;
}
