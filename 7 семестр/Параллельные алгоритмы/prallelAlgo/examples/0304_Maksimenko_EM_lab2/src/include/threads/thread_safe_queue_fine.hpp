#ifndef FINE_GRAINED_THREAD_SAFE_QUEUE_HPP
#define FINE_GRAINED_THREAD_SAFE_QUEUE_HPP

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <memory>

namespace threads
{

template < typename T >
class ThreadSafeQueue
{
public:
    ThreadSafeQueue()
        : canceled_{ false }
    {
        tail_ = std::make_shared< Node >( nullptr, nullptr ); // null node
        head_ = tail_; // queue is empty
    } // ctor
    
    ThreadSafeQueue( const ThreadSafeQueue& ) = delete;
    ThreadSafeQueue& operator=( const ThreadSafeQueue& ) = delete;

    /// @brief Добавление элемента в очередь.
    /// @param[in] value Добавляемый элемент.
    /// @details Добавляется элемент value в очередь.
    /// и сигнализируется условной переменной.
    /// @return Удалось ли добавить элемент.
    bool push( T&& value )
    {
        if ( canceled_.load( std::memory_order_acquire ) )
        {
            return false;
        }
        std::shared_ptr< Node > newTail = std::make_shared< Node >( nullptr, nullptr );

        std::unique_lock< std::mutex > tailLockGuard{ tailMtx_ };
        tail_->next = newTail;
        tail_->value = std::make_shared< T >( std::move( value ) );
        tail_ = newTail;
        cond_.notify_one();
        return true;
    } // push

    /// @brief Извлечение элемента из очереди.
    /// @details Извлекается элемент из очереди,
    /// если элемента нет - поток блокируется.
    /// @return Извлекаемый элемент.
    std::shared_ptr< T > popAndWait()
    {
        if ( canceled_.load( std::memory_order_acquire ) )
        {
            return nullptr;
        }
        std::shared_ptr< Node > node = waitPopHead();
        return node.get() ? node->value : nullptr;
    } // popAndWait

    /// @brief Отмена операций с очередью.
    /// @details Отмена всех операций в очереди и запрет новых.
    void cancel()
    {
        canceled_.store( true, std::memory_order_release );
        cond_.notify_all();
    } // cancel
private:
    struct Node
    {
        Node( std::shared_ptr< T > val = nullptr, std::shared_ptr< Node > n = nullptr )
            : value{ val }, next{ n }
        {}

        std::shared_ptr< T > value;
        std::shared_ptr< Node > next;
    }; // Node

    std::shared_ptr< Node > getTail()
    {
        std::unique_lock< std::mutex > tailLockGuard{ tailMtx_ };
        return tail_;
    } // getTail

    std::shared_ptr< Node > popHeadData()
    {
        /// no tail check, because checked outside
        std::shared_ptr< Node > oldHead = head_;
        head_ = head_->next;
        return oldHead;
    } // popHeadData

    std::unique_lock< std::mutex > waitData()
    {
        std::unique_lock< std::mutex > headLockGuard{ headMtx_ };
        cond_.wait( headLockGuard, [ this ]() {
            return getTail() != head_ || canceled_.load( std::memory_order_acquire );
        } );
        return headLockGuard;
    } // waitData

    std::shared_ptr< Node > waitPopHead()
    {
        std::unique_lock< std::mutex > headLockGuard( waitData() );
        if ( canceled_.load( std::memory_order_acquire ) )
        {
            return nullptr;
        }
        return popHeadData();
    } // waitPopHead

    std::shared_ptr< Node > head_;
    std::shared_ptr< Node > tail_;

    std::mutex headMtx_;
    std::mutex tailMtx_;

    std::condition_variable cond_;
    std::atomic_bool canceled_;

}; // ThreadSafeQueue

} // namespace threads

#endif // FINE_GRAINED_THREAD_SAFE_QUEUE_HPP
