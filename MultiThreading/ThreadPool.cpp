#include "ThreadPool.h"

ThreadPool::ThreadPool() :
	m_cores(thread::hardware_concurrency() - 1),
	m_currentCore(0)
{
	for (int i = 0; i < m_cores; i++)
	{
		m_threads.push_back(thread(loop, ref(*this)));
	}
}

ThreadPool::~ThreadPool()
{
	unique_lock<mutex> lock(m_queueMutex);
	m_terminate = true;

	condition.notify_all(); // wake up all threads.

	// Join all threads.
	for (std::thread& every_thread : m_threads)
	{
		every_thread.join();
	}

	m_threads.clear();
}

void ThreadPool::addTask(std::function<void()> t_task)
{
	{
		unique_lock<mutex> lock(m_queueMutex);
		m_tasks.push(t_task);
	}
	condition.notify_one();
}

void ThreadPool::loop(ThreadPool& t_pool)
{
	while (true)
	{
		function<void()> task = function<void()>();
		{
			unique_lock<mutex> lock(t_pool.m_queueMutex);
			t_pool.condition.wait(lock, [&] {return !t_pool.m_tasks.empty() ||  t_pool.m_terminate; });
			task = t_pool.m_tasks.front();
			t_pool.m_tasks.pop();
		}
		task();
	}
}
