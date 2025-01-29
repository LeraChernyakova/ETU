#ifndef THREADS_THREAD_SAFE_QUEUE_HPP
#define THREADS_THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <type_traits>
#if defined( ALLOW_SHARED_LOCKS )
#include <shared_mutex>
#else // !defined( ALLOW_SHARED_LOCKS )
#include <mutex>
#endif // defined( ALLOW_SHARED_LOCKS )
#include <iostream>


namespace threads
{

template < typename T >
class ThreadSafeQueue
{
public:
    ThreadSafeQueue()
        : canceled_{ false }
    {}
    ThreadSafeQueue( const ThreadSafeQueue& ) = delete;
    ThreadSafeQueue& operator=( const ThreadSafeQueue& ) = delete;

    void cancel()
    {
#if defined( ALLOW_SHARED_LOCKS )
        std::unique_lock< std::shared_mutex > lockGuard{ mtx_ };
#else // !defined( ALLOW_SHARED_LOCKS )
        std::unique_lock< std::mutex > lockGuard{ mtx_ };
#endif // defined( ALLOW_SHARED_LOCKS )
        canceled_.store( true, std::memory_order_release );
        cond_.notify_all();
    } // cancel

    bool push( T&& value )
    {
        if ( canceled_.load( std::memory_order_acquire ) )
        {
            return false;
        }
#if defined( ALLOW_SHARED_LOCKS )
        std::unique_lock< std::shared_mutex > lockGuard{ mtx_ };
#else // !defined( ALLOW_SHARED_LOCKS )
        std::unique_lock< std::mutex > lockGuard{ mtx_ };
#endif // defined( ALLOW_SHARED_LOCKS )
        container_.push( value );
        cond_.notify_one();
        return true;
    } // push

    std::shared_ptr< T > popAndWait()
    {
        std::shared_ptr< T > value = nullptr;
        while ( true )
        {
#if defined( ALLOW_SHARED_LOCKS )
            std::unique_lock< std::shared_mutex > lockGuard{ mtx_ };
#else // !defined( ALLOW_SHARED_LOCKS )
            std::unique_lock< std::mutex > lockGuard{ mtx_ };
#endif // defined( ALLOW_SHARED_LOCKS )
            cond_.wait( lockGuard, [ this ](){
                return !container_.empty() || canceled_.load( std::memory_order_acquire );
            } );
            if ( canceled_.load( std::memory_order_acquire ) )
            {
                /// Окончание работы
                break;
            }
            value = std::make_shared< T >( container_.front() );
            container_.pop();
            break;
        }
        return value;
    } // popAndWait

private:
#if defined( ALLOW_SHARED_LOCKS )
    mutable std::shared_mutex mtx_;     ///< Мьютекс для синхронизации операций с очередью.
#else // !defined( ALLOW_SHARED_LOCKS )
    mutable std::mutex mtx_;            ///< Мьютекс для синхронизации операций с очередью.
#endif // defined( ALLOW_SHARED_LOCKS )
    std::queue< T > container_;         ///< Очередь.
    std::condition_variable cond_;      ///< Условная переменная для синхронизации операций с очередью.
    std::atomic_bool canceled_;         ///< Атомарный флаг нужно ли закончить обработку очереди.

}; // class ThreadSafeQueue

} // namespace threads

#endif // THREADS_THREAD_SAFE_QUEUE_HPP
