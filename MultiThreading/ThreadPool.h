#pragma once

#include <iostream>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	void addTask(function<void()> t_task);
	static void loop(ThreadPool& t_pool);
private:
	vector<thread> m_threads;
	queue<function<void()>> m_tasks;
	int m_cores;
	int m_currentCore;
	mutex m_queueMutex;
	condition_variable condition;
	bool m_terminate;
};