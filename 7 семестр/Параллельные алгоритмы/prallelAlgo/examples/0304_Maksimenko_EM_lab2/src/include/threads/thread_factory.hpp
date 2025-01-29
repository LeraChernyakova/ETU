#ifndef THREADS_THREAD_FACTORY_HPP
#define THREADS_THREAD_FACTORY_HPP

#include <thread>
#include <vector>
#include <functional>
#include <atomic>
#include <mutex>
#if defined( FINE_GRAINED_LOCK )
#include "threads/thread_safe_queue_fine.hpp"
#else // !defined( FINE_GRAINED_LOCK )
#include "threads/thread_safe_queue.hpp"
#endif // defined( FINE_GRAINED_LOCK )

namespace threads
{

template < typename Task >
class ThreadFactory
{
public:
    ThreadFactory()
    {}

    ~ThreadFactory()
    {
        tasks_.cancel();
        wait();
    } // ~ThreadFactory

    void wait()
    {
        for ( auto& producer: producers_ )
        {
            producer.join();
        }
        producers_.clear();
        for ( auto& consumer: consumers_ )
        {
            consumer.join();
        }
        consumers_.clear();
    } // wait

    bool addTask( Task&& task )
    {
        return tasks_.push( std::move( task ) );
    }

    std::shared_ptr< Task > getTask()
    {
        return tasks_.popAndWait();
    }

    void addProducer( const std::function< Task ( void ) >& producer, size_t limit = 0 )
    {
        std::unique_lock< std::mutex > lockGuard{ producersMtx_ };
        producers_.emplace_back( &ThreadFactory::produce, this, producer, limit );
    } // addProducer

    void addConsumer( const std::function< void( const Task& ) >& consumer, size_t limit = 0 )
    {
        std::unique_lock< std::mutex > lockGuard{ producersMtx_ };
        producers_.emplace_back( &ThreadFactory::consume, this, consumer, limit );
    } // addConsumer

private:
    void produce( std::function< Task ( void ) > producer, size_t limit = 0 )
    {
        bool infinite = ( 0 == limit );
        while ( infinite || 0 < limit-- )
        {
            Task task = producer();
            if ( !addTask( std::move( task ) ) )
            {
                break;
            }
        }
    } // produce

    void consume( std::function< void( const Task& ) > consumer, size_t limit = 0 )
    {
        bool infinite = ( 0 == limit );
        std::shared_ptr< Task > task;
        while ( infinite || 0 < limit-- )
        {
            task = getTask();
            if ( !task.get() )
            {
                break;
            }
            consumer( *task.get() );
        }
    } // consume

private:
    std::mutex producersMtx_;
    std::mutex concumersMtx_;
    std::vector< std::thread > producers_;
    std::vector< std::thread > consumers_;
    ThreadSafeQueue< Task > tasks_;
}; // class ThreadFactory

} // namespace threads

#endif // THREADS_THREAD_FACTORY_HPP
