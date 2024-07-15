#pragma once
#include <string>

namespace acp
{
	class ZLibException : public std::exception
	{
		int code;

	public:
		explicit ZLibException(int code);

		const char* what() const noexcept override;
	};
}
