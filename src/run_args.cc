#include "run_args.hh"

#include "util/profiler/profiler.hh"

constexpr std::string_view PREFIX = "--";
std::string BIN_PATH;

acp::RunArgs::RunArgs(int argc, char* argv[])
{
	ProfilerStackGuard guard = Profiler::get().pushGuard("RunArgs()");

	BIN_PATH = argv[0];

	std::string currentArg;
	std::string currentVal;

	for (int i = 1; i < argc; i++)
	{
		const std::string arg = argv[i];

		if (arg.starts_with(PREFIX))
		{
			if (!currentArg.empty() && currentVal.empty()) // flag, next
				flags.push_back(currentArg);
			else if (!currentArg.empty() && !currentVal.empty()) // arg, next
			{
				args.insert_or_assign(currentArg, currentVal);
				currentVal.clear();
			}

			currentArg = arg.substr(PREFIX.length());
		}
		else
		{
			if (currentVal.empty())
				currentVal = arg;
			else
				currentVal += ' ' + arg;
		}
	}

	if (!currentArg.empty() && currentVal.empty()) // flag
		flags.push_back(currentArg);
	else if (!currentArg.empty() && !currentVal.empty()) // arg
		args.insert_or_assign(currentArg, currentVal);
}

bool acp::RunArgs::hasFlag(const std::string& name) const
{
	return std::ranges::find(flags, name) != flags.end();
}

std::optional<std::string> acp::RunArgs::getArg(const std::string& name) const
{
	const auto& pair = args.find(name);
	if (pair == args.end())
		return std::nullopt;

	return std::make_optional(pair->second);
}


const std::string& acp::RunArgs::getBinPath()
{
	return BIN_PATH;
}
