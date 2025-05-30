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


std::vector<std::string> acp::StrUtils::split(std::string str, const std::string& delim)
{
	std::vector<std::string> arr;

	size_t pos;
	while ((pos = str.find(delim)) != std::string::npos)
	{
		arr.push_back(str.substr(0, pos));
		str.erase(0, pos + delim.length());
	}
	arr.push_back(str);

	return arr;
}

std::string acp::StrUtils::join(const std::vector<std::string>& arr, const std::string& delim)
{
	std::string str;

	for (int i = 0; i < arr.size(); ++i)
	{
		str += arr[i];

		if (i + 1 < arr.size())
			str += delim;
	}

	return str;
}

std::string acp::StrUtils::toLowerCase(const std::string& str)
{
	std::string ret;
	ret.reserve(str.length());

	for (const char c : str)
		ret += std::tolower(c);

	return ret;
}

std::string acp::StrUtils::toUpperCase(const std::string& str)
{
	std::string ret;
	ret.reserve(str.length());

	for (const char c : str)
		ret += std::toupper(c);

	return ret;
}

std::vector<std::string> acp::StrUtils::retMatches(const std::string& arg, const std::vector<std::string>& args)
{
	const std::string lowerArg = toLowerCase(arg);

	std::vector<std::string> ret;
	for (const std::string& s : args)
	{
		if (s.length() >= arg.length() && lowerArg == toLowerCase(s.substr(0, arg.length())))
			ret.push_back(s);
	}

	return ret;
}
