#pragma once
#include "command/i_command_source.hh"

namespace acp
{
	class TerminalCommandSource : public ICommandSource
	{
	public:
		void sendMessage(std::unique_ptr<text::Component>&& message) override;
		bool hasPermission(const Permission& permission) const override;
	};
}
