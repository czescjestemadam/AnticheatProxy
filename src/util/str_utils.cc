#include "str_utils.hh"

void acp::StrUtils::replace(std::string& str, const std::string& from, const std::string& to)
{
	size_t pos = 0;

	while (true)
	{
		pos = str.find(from, pos);
		if (pos == std::string::npos)
			break;

		str = str.replace(pos, from.length(), to);
		pos += to.length();
	}
}

std::string acp::StrUtils::replaced(const std::string& str, const std::string& from, const std::string& to)
{
	std::string replaced = str;
	replace(replaced, from, to);
	return replaced;
}
