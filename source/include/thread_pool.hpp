#pragma once

#include <vector>
#include <thread>
#include <list>
#include <mutex>
#include <functional>

#include "spin_lock.hpp"
class Task
{
public:
	virtual void run() = 0;
};

class ThreadPool
{
public:
	ThreadPool(size_t thread_count = 0);
	~ThreadPool();

	static void WorkThread(ThreadPool *master);
	void addTask(Task *task);
	Task *getTask();

	void parallelFor(size_t width, size_t height, const std::function<void(size_t, size_t)> &lambda);
	void wait() const;

private:
	std::vector<std::thread> mThreads;
	std::list<Task *> mTasks;
	SpinLock mLock{};
	std::atomic<int> mAlive;
};
