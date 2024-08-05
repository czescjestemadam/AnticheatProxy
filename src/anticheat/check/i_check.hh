#pragma once
#include <string>

namespace acp
{
	class ICheck
	{
	public:
		virtual ~ICheck() = default;

		virtual std::string getName() const = 0;

		virtual std::string toString() const = 0;
	};
}
