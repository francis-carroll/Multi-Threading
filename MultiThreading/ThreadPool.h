#pragma once

#include <iostream>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;

/// <summary>
/// Class used for pooling threads and executing tasks within the threads
/// </summary>
class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();

	void addTask(function<void()> t_task);

	queue<function<void()>> getTasks();
private:
	static void threadLoop(ThreadPool& t_pool);

	vector<thread> m_threads;
	queue<function<void()>> m_tasks;
	int m_activeThreads;
	mutex m_queueMutex;
	condition_variable m_conditionVariable;
	bool m_terminate;
};