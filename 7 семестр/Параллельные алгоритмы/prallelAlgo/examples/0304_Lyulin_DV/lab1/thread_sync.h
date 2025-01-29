#ifndef THREAD_SYNC_H
#define THREAD_SYNC_H

#include <thread>
#include <atomic>
#include <condition_variable>

struct ThreadSync
{
public:
     void wait();
     void notify();

private:
     std::condition_variable cond_;
     std::mutex mtx_;
     std::atomic_bool ready_{ false }; // flag for dealing with spurious and lost wakeups
};

#endif // THREAD_SYNC_H
