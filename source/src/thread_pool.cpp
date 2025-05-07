#include "thread_pool.hpp"

ThreadPool::ThreadPool(size_t thread_count)
{
	mAlive = true;
	if (thread_count == 0)
	{
		thread_count = std::thread::hardware_concurrency();
	}

	for (size_t i = 0; i < thread_count; i++)
	{
		mThreads.push_back(std::thread(ThreadPool::WorkThread, this));
	}
}

ThreadPool::~ThreadPool()
{
	while (!mTasks.empty())
	{
		std::this_thread::yield();
	}
	mAlive = false;
	for (auto& thread : mThreads)
	{
		thread.join();
	}
	mThreads.clear();
}

void ThreadPool::WorkThread(ThreadPool* master)
{
	if (master)
	{
		while (master->mAlive)
		{
			Task* task = master->getTask();
			if (task)
			{
				task->run();
			}else{
				std::this_thread::yield();
			}
		}
	}
}

void ThreadPool::addTask(Task* task)
{
	std::lock_guard<std::mutex> guard(mLock);
	mTasks.push_back(task);
}
Task* ThreadPool::getTask()
{
	std::lock_guard<std::mutex> guard(mLock);
	if (mTasks.empty())
	{
		return nullptr;
	}
	Task* task = mTasks.front();
	mTasks.pop_front();
	return task;
}