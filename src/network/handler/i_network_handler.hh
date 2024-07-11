#pragma once

namespace acp
{
	class Connection;

	class INetworkHandler
	{
	protected:
		const Connection* connection;

	public:
		explicit INetworkHandler(const Connection* connection);
		virtual ~INetworkHandler() = default;

		// TODO reason
		virtual void disconnect();
	};
}
