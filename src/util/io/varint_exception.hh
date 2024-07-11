#pragma once
#include <exception>

namespace acp
{
	class VarintException : public std::exception
	{
	public:
		const char* what() const noexcept override;
	};
}
