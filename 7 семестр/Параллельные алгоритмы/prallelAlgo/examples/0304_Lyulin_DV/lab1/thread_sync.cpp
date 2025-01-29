#include <thread_sync.h>

void ThreadSync::wait()
{
     std::unique_lock< std::mutex > lock( mtx_ );
     cond_.wait( lock, [ this ](){ return ready_.load( std::memory_order_relaxed ); } );
}


void ThreadSync::notify()
{
     std::unique_lock< std::mutex > lock( mtx_ );
     ready_.store( true, std::memory_order_relaxed );
     cond_.notify_one();
}
