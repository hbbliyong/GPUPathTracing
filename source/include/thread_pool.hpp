#pragma once

#include <vector>
#include <thread>
#include <list>
#include <mutex>
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

	static void WorkThread(ThreadPool* master);
	void addTask(Task* task);
	Task* getTask();
private:
	std::vector<std::thread> mThreads;
	std::list<Task*> mTasks;
	std::mutex mLock;
	bool mAlive = false;
};
