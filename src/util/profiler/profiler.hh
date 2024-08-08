#pragma once
#include <chrono>
#include <string>
#include <unordered_map>

namespace acp
{
	struct CompiledProfilerSample;

	struct ProfilerSample
	{
		using clk = std::chrono::steady_clock;

		clk::time_point start, end;
		clk::duration time;

		explicit ProfilerSample(const clk::time_point& start);
	};

	struct CompiledProfilerSample
	{
		using clk = std::chrono::steady_clock;

		size_t count;
		clk::time_point first, last;
		clk::duration min, max, avg, median, time;

		explicit CompiledProfilerSample(size_t count, const clk::duration& min, const clk::duration& max);
	};

	class Profiler
	{
		std::unordered_map<std::string, std::vector<ProfilerSample>> finished;
		std::vector<std::pair<std::string, ProfilerSample>> pending;

	public:
		void push(const std::string& name);
		ProfilerSample pop();

		const std::unordered_map<std::string, std::vector<ProfilerSample>>& getSamples() const;
		std::unordered_map<std::string, CompiledProfilerSample> getCompiledSamples();
	};
}
