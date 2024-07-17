#pragma once

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

		// TODO reason
		virtual void disconnect();
	};
}
