#pragma once
#include <string>

namespace acp
{
	class Connection;

	class ICheck
	{
	protected:
		Connection* connection;
		int count = 0;
		int failCount = 0;

	public:
		explicit ICheck(Connection* connection);
		virtual ~ICheck() = default;

		void fail(bool sendAlert = false, const std::string& info = "");

		int getCount() const;
		int getFailCount() const;

		virtual std::string getName() const = 0;
		virtual std::string getDescription() const = 0;
	};
}
