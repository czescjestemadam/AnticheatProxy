#pragma once
#include "util/text/component.hh"

namespace acp
{
	class Connection;

	class INetworkHandler
	{
	protected:
		Connection* connection;

	public:
		explicit INetworkHandler(Connection* connection);
		virtual ~INetworkHandler() = default;

		virtual void disconnect(const std::unique_ptr<text::Component>& reason);
	};
}
