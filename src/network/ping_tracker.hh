#pragma once
#include <chrono>
#include <unordered_map>
#include <vector>

namespace acp
{
	class PingTracker
	{
		std::unordered_map<long, std::chrono::system_clock::time_point> keepAlives;
		std::vector<int> samples;

	public:
		void onSend(long id);
		void onReceive(long id);

		const std::vector<int>& getSamples() const;

		int getAvg() const;
		int getAvgLast(int num) const;

		int getLast() const;

		void add(int sample);


		static int getMaxSampleSize();
	};
}
