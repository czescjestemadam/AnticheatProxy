#pragma once
#include <string>

namespace acp
{
	class Permission;

	class ICommandSource
	{
	public:
		virtual ~ICommandSource() = default;

		virtual void sendMessage(const std::string& message) = 0;

		virtual bool hasPermission(const Permission* permission) const = 0;
	};
}
