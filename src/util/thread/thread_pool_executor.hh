#pragma once
#include <condition_variable>
#include <functional>
#include <queue>
#include <thread>
#include <vector>

namespace acp
{
	class ThreadPoolExecutor
	{
		std::atomic_bool running = true;
		std::vector<std::thread> threads;

		std::queue<std::function<void()>> tasks;
		std::mutex tasksMx;
		std::condition_variable tasksCv;

		std::mutex tasksEmptyMx;
		std::condition_variable tasksEmptyCv;

	public:
		explicit ThreadPoolExecutor(size_t threadCount);
		~ThreadPoolExecutor();

		void queue(const std::function<void()>& func);

		void wait();
		void stop();
		void waitStop();


		/**
		 * craetes ThradPoolExecutor with <code>threadCount = std::thread::hardware_concurrency()</code>
		 */
		static ThreadPoolExecutor createDefault();

	private:
		void taskLoop();
	};
}
