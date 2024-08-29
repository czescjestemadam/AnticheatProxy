#pragma once
#include "util/text/component.hh"

#include <memory>

namespace acp
{
	class Permission;

	class ICommandSource
	{
	public:
		virtual ~ICommandSource() = default;

		/// sends copied component
		void sendMessage(const std::unique_ptr<text::Component>& message);
		virtual void sendMessage(std::unique_ptr<text::Component>&& message) = 0;

		bool hasPermission(const Permission* permission) const;
		virtual bool hasPermission(const Permission& permission) const = 0;
	};
}
