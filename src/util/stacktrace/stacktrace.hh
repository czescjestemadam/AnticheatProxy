#pragma once
#include <string>
#include <vector>

namespace acp
{
	class Stacktrace
	{
		std::vector<std::string> traces;

	public:
		Stacktrace() = default;
		explicit Stacktrace(const std::vector<std::string>& traces);

		const std::vector<std::string>& getTraces() const;

		std::string toString() const;


		static Stacktrace get(int size = 16, int skip = 1);
	};
}
