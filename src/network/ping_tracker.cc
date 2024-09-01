#include "ping_tracker.hh"

#include "anticheat_proxy.hh"

void acp::PingTracker::onSend(long id)
{
	keepAlives[id] = std::chrono::system_clock::now();
}

void acp::PingTracker::onReceive(long id)
{
	const auto now = std::chrono::system_clock::now();

	if (keepAlives.contains(id))
	{
		const auto time = now - keepAlives[id];
		add(static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(time).count()));
		keepAlives.erase(id);
	}
}

const std::vector<int>& acp::PingTracker::getSamples() const
{
	return samples;
}

int acp::PingTracker::getAvg() const
{
	return getAvgLast(static_cast<int>(samples.size()));
}

int acp::PingTracker::getAvgLast(int num) const
{
	int sum = 0;
	int count = 0;

	for (int i = static_cast<int>(samples.size()) - 1; i >= 0; --i)
	{
		sum += samples[i];
		count++;

		if (--num < 0)
			break;
	}

	return count == 0 ? -1 : sum / count;
}

int acp::PingTracker::getLast() const
{
	return samples.empty() ? -1 : samples.back();
}

void acp::PingTracker::add(int sample)
{
	samples.push_back(sample);
	if (samples.size() > getMaxSampleSize())
		samples.erase(samples.begin());
}


int acp::PingTracker::getMaxSampleSize()
{
	return AnticheatProxy::get()->getConfigManager().getNetwork().pingTrackerSamplesCount;
}
