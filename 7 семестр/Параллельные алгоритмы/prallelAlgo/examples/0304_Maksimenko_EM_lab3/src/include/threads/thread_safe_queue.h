#ifndef THREADS_THREAD_SAFE_QUEUE_H
#define THREADS_THREAD_SAFE_QUEUE_H

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace threads
{

template < typename T >
class ThreadSafeQueue
{
private:
    struct Node
    {
        Node( std::shared_ptr< T > val = nullptr, Node* n = nullptr )
            : value{ val }, next{ n }
        {}

        std::shared_ptr< T > value;
        std::atomic< Node* > next;
    }; // Node

public:
    ThreadSafeQueue( size_t threadsCount );
    ~ThreadSafeQueue();
    
    ThreadSafeQueue( const ThreadSafeQueue& ) = delete;
    ThreadSafeQueue& operator=( const ThreadSafeQueue& ) = delete;

    /// @brief Добавление элемента в очередь.
    /// @param[in] value Добавляемый элемент.
    void push( T&& value );

    /// @brief Извлечение элемента из очереди.
    /// @return Извлекаемый элемент или nullptr, если очередь пуста.
    std::shared_ptr< T > pop();

private:
    void initThreadId();
    std::atomic< Node* >& getHazardPointer( size_t number );
    void retire( Node* node );
    void scan();

private:

    static size_t threadCounter_;
    static constexpr size_t hazardPointersPerThread_    = 2;
    static constexpr size_t batchSize_                  = 2;

    std::atomic< Node* > head_;
    std::atomic< Node* > tail_;

    std::vector< std::atomic< Node* > > hazardPointers_;
    std::vector< Node* > retireList_;
    std::vector< size_t > retireCounts_;

    static thread_local std::atomic< size_t > threadId_;

}; // ThreadSafeQueue

} // namespace threads

#include "threads/thread_safe_queue.hpp"

#endif // THREADS_THREAD_SAFE_QUEUE_H
