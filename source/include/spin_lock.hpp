#include <atomic>
#include <thread>

class SpinLock
{
public:
    void acquire()
    {
        while (mFlag.test_and_set(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
    }
    void release() { mFlag.clear(std::memory_order_release); }

private:
    std::atomic_flag mFlag = ATOMIC_FLAG_INIT;
};

class Guard
{
public:
    Guard(SpinLock &spin_lock) : mSpin_lock(spin_lock) { mSpin_lock.acquire(); }
    ~Guard() { mSpin_lock.release(); }

private:
    SpinLock &mSpin_lock;
};