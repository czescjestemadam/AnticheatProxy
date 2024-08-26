#pragma once
#include <string>

namespace acp
{
	struct Alert
	{
		std::string username;
		std::string check;
		std::string checkInfo;
		std::string checkDescription;
		int count;
	};
}
