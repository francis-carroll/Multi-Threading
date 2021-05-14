#include "ThreadPool.h"

ThreadPool::ThreadPool() :
	m_activeThreads(thread::hardware_concurrency() - 1),
	m_terminate(false),
	m_closed(false)
{
	//add the loops to the availble threads.
	for (int i = 0; i < m_activeThreads; i++)
	{
		m_threads.push_back(thread(threadLoop, ref(*this)));
	}
}

ThreadPool::~ThreadPool()
{
	if (!m_closed)
	{
		closeThreads();
	}
}

/// <summary>
/// Adds a task to the queue for processing within a thread
/// </summary>
/// <param name="t_task"></param>
void ThreadPool::addTask(std::function<void()> t_task)
{
	{
		unique_lock<mutex> lock(m_queueMutex);
		m_tasks.push(t_task);
	}
	//notify thread that a task has been added
	m_conditionVariable.notify_one();
}

queue<function<void()>> ThreadPool::getTasks()
{
	unique_lock<mutex> lock(m_queueMutex);
	return m_tasks;
}

void ThreadPool::threadLoop(ThreadPool& t_pool)
{
	while (!t_pool.m_terminate)
	{
		function<void()> task = function<void()>();
		{
			unique_lock<mutex> lock(t_pool.m_queueMutex);

			//if the task queue is not empty or it has been terminated wait
			t_pool.m_conditionVariable.wait(lock, [&] {return !t_pool.m_tasks.empty() ||  t_pool.m_terminate; });

			//take the next task
			task = t_pool.m_tasks.front();

			//pop the queue
			t_pool.m_tasks.pop();
		}
		//execute the task
		task();
	}
}

void ThreadPool::closeThreads()
{
	unique_lock<mutex> lock(m_queueMutex);
	m_terminate = true;

	//notify all threads to listen
	m_conditionVariable.notify_all();

	//join and destroy threads
	for (std::thread& thread : m_threads)
	{
		thread.join();
	}

	//clear the threads
	m_threads.clear();
	m_closed = true;
}
