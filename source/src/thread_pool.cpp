#include "thread_pool.hpp"
/**
 * 目前只支持主线程添加任务，如果是支持多线程添加任务，需要用两个锁来实现
 */
ThreadPool::ThreadPool(size_t thread_count)
{
	mAlive = 1;
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
	wait();

	mAlive = 0;
	for (auto &thread : mThreads)
	{
		thread.join();
	}
	mThreads.clear();
}

void ThreadPool::WorkThread(ThreadPool *master)
{
	if (master)
	{
		while (master->mAlive == 1)
		{
			Task *task = master->getTask();
			if (task)
			{
				task->run();
			}
			else
			{
				std::this_thread::yield();
			}
		}
	}
}

void ThreadPool::addTask(Task *task)
{
	Guard guard(mLock);
	mTasks.push(task);
}
Task *ThreadPool::getTask()
{
	Guard guard(mLock);
	if (mTasks.empty())
	{
		return nullptr;
	}
	Task *task = mTasks.front();
	mTasks.pop();
	return task;
}

class ParallelForTask : public Task
{
public:
	ParallelForTask(size_t x, size_t y, const std::function<void(size_t, size_t)> &lambda)
		: mX(x), mY(y), mLambda(lambda) {}

	void run() override
	{
		mLambda(mX, mY);
	}

private:
	size_t mX, mY;
	std::function<void(size_t, size_t)> mLambda;
};

void ThreadPool::parallelFor(size_t width, size_t height, const std::function<void(size_t, size_t)> &lambda)
{
	Guard guard(mLock);

	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			mTasks.push(new ParallelForTask(i, j, lambda));
		}
	}
}

void ThreadPool::wait() const
{
	while (!mTasks.empty())
	{
		std::this_thread::yield();
	}
}