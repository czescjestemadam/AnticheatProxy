#pragma once
#include <string>

namespace acp
{
	class CheckManager;

	class ICheck
	{
	protected:
		CheckManager* checkManager;

	public:
		explicit ICheck(CheckManager* checkManager);
		virtual ~ICheck() = default;

		void fail();

		virtual std::string toString() const = 0;
	};
}
