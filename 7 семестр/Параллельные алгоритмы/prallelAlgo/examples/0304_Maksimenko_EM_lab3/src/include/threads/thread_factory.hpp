#ifndef THREADS_THREAD_FACTORY_HPP
#define THREADS_THREAD_FACTORY_HPP

#include <thread>
#include <vector>
#include <functional>
#include <atomic>
#include <stdexcept>

#include "threads/thread_safe_queue.h"

namespace threads
{

template < typename Task >
class ThreadFactory
{
public:
    ThreadFactory(
          size_t producersCount
        , size_t consumersCount
        , size_t tasksCount
        , const std::function< Task ( void ) >& producer
        , const std::function< void( const Task& ) >& consumer
    )
        : producers_{}
        , consumers_{}
        , tasks_( producersCount + consumersCount )
    {
        if ( 0 != tasksCount % producersCount )
        {
            throw std::logic_error{ "Tasks count not valid for producers" };
        }
        if ( 0 != tasksCount % consumersCount )
        {
            throw std::logic_error{ "Tasks count not valid for consumers" };
        }
        size_t tasksForProducer = tasksCount / producersCount;
        size_t tasksForConsumer = tasksCount / consumersCount;

        producers_.reserve( producersCount );
        consumers_.reserve( consumersCount );

        for ( size_t i = 0; i < producersCount; ++i )
        {
            producers_.emplace_back( &ThreadFactory::produce, this, producer, tasksForProducer );
        }
        for ( size_t i = 0; i < consumersCount; ++i )
        {
            consumers_.emplace_back( &ThreadFactory::consume, this, consumer, tasksForConsumer );
        }
    }

    ~ThreadFactory()
    {
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

    void addTask( Task&& task )
    {
        tasks_.push( std::move( task ) );
    } // addTask

    std::shared_ptr< Task > getTask()
    {
        std::shared_ptr< Task > task = nullptr;
        while ( !task.get() )
        {
            task = tasks_.pop();
        }
        return task;
    } // getTask

private:
    void produce( std::function< Task ( void ) > producer, size_t limit = 0 )
    {
        bool infinite = ( 0 == limit );
        while ( infinite || 0 < limit-- )
        {
            Task task = producer();
            addTask( std::move( task ) );
        }
    } // produce

    void consume( std::function< void( const Task& ) > consumer, size_t limit = 0 )
    {
        bool infinite = ( 0 == limit );
        std::shared_ptr< Task > task;
        while ( infinite || 0 < limit-- )
        {
            task = getTask();
            consumer( *task.get() );
        }
    } // consume

private:
    std::vector< std::thread > producers_;
    std::vector< std::thread > consumers_;
    ThreadSafeQueue< Task > tasks_;
}; // class ThreadFactory

} // namespace threads

#endif // THREADS_THREAD_FACTORY_HPP
