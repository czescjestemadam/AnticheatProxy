#pragma once
#include "i_command_source.hh"

#include <vector>

namespace acp
{
	class Permission;
	class AcpPlayer;

	class ICommand
	{
	protected:
		const Permission* permission;

	public:
		explicit ICommand(const Permission* permission);
		virtual ~ICommand() = default;

		virtual void execute(ICommandSource* source, const std::vector<std::string>& args) = 0;
		virtual std::vector<std::string> complete(ICommandSource* source, const std::vector<std::string>& args) = 0;

		const Permission* getPermission() const;

	protected:
		// TODO args helper methods
	};
}
