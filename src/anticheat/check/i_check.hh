#pragma once
#include <string>

namespace acp
{
	class CheckManager;

	class ICheck
	{
	protected:
		CheckManager* checkManager;
		int failCount = 0;

	public:
		explicit ICheck(CheckManager* checkManager);
		virtual ~ICheck() = default;

		void fail();
		void alert(const std::string& info = "");

		int getFailCount() const;

		virtual std::string toString() const = 0;
	};
}
