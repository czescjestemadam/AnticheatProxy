#pragma once
#include <string>

namespace acp
{
	template<class T>
	struct EnumNames
	{
		static std::string get(T val);
	};
}
