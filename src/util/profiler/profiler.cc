#include "profiler.hh"

#include <cmath>

acp::ProfilerSample::ProfilerSample(const clk::time_point& start) : start(start), time(-1)
{
}


acp::CompiledProfilerSample::CompiledProfilerSample(size_t count, const clk::duration& min, const clk::duration& max)
	: count(count),
	  first(clk::time_point::max()),
	  last(clk::time_point::min()),
	  min(min),
	  max(max),
	  avg(),
	  median(),
	  time(clk::duration::zero())
{
}


void acp::Profiler::push(const std::string& name)
{
	const ProfilerSample sample(ProfilerSample::clk::now());
	pending.emplace_back(name, sample);
}

acp::ProfilerSample acp::Profiler::pop()
{
	if (pending.empty())
		return ProfilerSample(ProfilerSample::clk::time_point::min());

	const auto now = ProfilerSample::clk::now();

	auto [name, sample] = pending.back();
	pending.pop_back();
	sample.end = now;
	sample.time = sample.end - sample.start;

	auto& samples = finished[name];
	samples.push_back(sample);

	return sample;
}

acp::ProfilerStackGuard acp::Profiler::pushGuard(const std::string& name)
{
	push(name);
	return ProfilerStackGuard(*this);
}

const std::unordered_map<std::string, std::vector<acp::ProfilerSample>>& acp::Profiler::getSamples() const
{
	return finished;
}

std::unordered_map<std::string, acp::CompiledProfilerSample> acp::Profiler::getCompiledSamples()
{
	std::unordered_map<std::string, CompiledProfilerSample> compiledSamples;

	for (auto& [name, samples] : finished)
	{
		std::sort(samples.begin(), samples.end(), [](const auto& lhs, const auto& rhs) { return lhs.time < rhs.time; });

		CompiledProfilerSample compiled(samples.size(), samples.front().time, samples.back().time);

		for (ProfilerSample sample : samples)
		{
			if (sample.start < compiled.first)
				compiled.first = sample.start;

			if (sample.end > compiled.last)
				compiled.last = sample.end;

			compiled.time += sample.time;
		}

		compiled.avg = compiled.time / compiled.count;

		if (compiled.count % 2) // odd
			compiled.median = samples[compiled.count / 2].time;
		else // even
		{
			const double halfCount = static_cast<double>(compiled.count) / 2.0;
			compiled.median = (samples[std::floor(halfCount)].time + samples[std::ceil(halfCount)].time) / 2;
		}

		compiledSamples.insert_or_assign(name, compiled);
	}

	return compiledSamples;
}


acp::ProfilerStackGuard::ProfilerStackGuard(Profiler& profiler) : profiler(profiler)
{
}

acp::ProfilerStackGuard::~ProfilerStackGuard()
{
	profiler.pop();
}
