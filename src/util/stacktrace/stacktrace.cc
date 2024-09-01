#include "stacktrace.hh"

#include "util/str_utils.hh"
#include "util/system.hh"

#include <execinfo.h>
#include <format>

acp::Stacktrace::Stacktrace(const std::vector<std::string>& traces)
	: traces(traces)
{
}

const std::vector<std::string>& acp::Stacktrace::getTraces() const
{
	return traces;
}

std::string acp::Stacktrace::toString() const
{
	return "\t" + StrUtils::join(traces, "\n\t");
}


acp::Stacktrace acp::Stacktrace::get(int size, int skip)
{
	Stacktrace trace;

	void* arr[size];
	const int num = backtrace(arr, size);
	char** traces = backtrace_symbols(arr, num);

	try
	{
		for (int i = skip; i < num; ++i)
		{
			const std::vector<std::string> traceArgs = StrUtils::split(traces[i]);
			const std::string file = traceArgs[0].substr(0, traceArgs[0].find('('));
			const std::string offset = traceArgs[0].substr(traceArgs[0].find('(') + 1, 8);

			const std::vector<std::string> out = StrUtils::split(
				System::execute(std::format("addr2line -e {} -C -f -s {}", file, offset)),
				"\n"
			);

			trace.traces.push_back(std::format("{} ({} {} {})", out[0], out[1], offset, traceArgs[1]));
		}
	}
	catch (...)
	{
	}

	free(traces);

	return trace;
}
