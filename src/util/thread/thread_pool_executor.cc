#include "thread_pool_executor.hh"

acp::ThreadPoolExecutor::ThreadPoolExecutor(size_t threadCount)
{
	for (int i = 0; i < threadCount; ++i)
		threads.emplace_back(&ThreadPoolExecutor::taskLoop, this);
}

acp::ThreadPoolExecutor::~ThreadPoolExecutor()
{
	waitStop();
}

void acp::ThreadPoolExecutor::queue(const std::function<void()>& func)
{
	{
		std::unique_lock lock(tasksMx);
		tasks.push(func);
	}

	tasksCv.notify_one();
}

void acp::ThreadPoolExecutor::wait()
{
	std::unique_lock lock(tasksEmptyMx);
	tasksEmptyCv.wait(lock);
}

void acp::ThreadPoolExecutor::stop()
{
	running = false;
}

void acp::ThreadPoolExecutor::waitStop()
{
	stop();

	tasksCv.notify_all();
	for (std::thread& thread : threads)
		thread.join();

	threads.clear();
}


acp::ThreadPoolExecutor acp::ThreadPoolExecutor::createDefault()
{
	return ThreadPoolExecutor(std::thread::hardware_concurrency());
}


void acp::ThreadPoolExecutor::taskLoop()
{
	while (running)
	{
		std::function<void()> task;

		{
			std::unique_lock lock(tasksMx);

			while (tasks.empty() && running)
			{
				tasksEmptyCv.notify_all();
				tasksCv.wait(lock);
			}

			if (tasks.empty() && !running)
				return;

			task = std::move(tasks.front());
			tasks.pop();
		}

		task();
	}
}
