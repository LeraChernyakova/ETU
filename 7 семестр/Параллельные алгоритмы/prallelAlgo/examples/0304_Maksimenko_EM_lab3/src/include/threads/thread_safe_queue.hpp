#ifndef THREADS_THREAD_SAFE_QUEUE_HPP
#define THREADS_THREAD_SAFE_QUEUE_HPP

#include <unordered_set>

namespace threads
{

template< typename T >
size_t ThreadSafeQueue< T >::threadCounter_{ 0 };

template< typename T >
thread_local std::atomic< size_t > ThreadSafeQueue< T >::threadId_{ static_cast< size_t >( -1 ) };


template< typename T >
ThreadSafeQueue< T >::ThreadSafeQueue( size_t threadsCount )
    : hazardPointers_{ hazardPointersPerThread_ * threadsCount }
    , retireList_{ batchSize_ * threadsCount * hazardPointersPerThread_ * threadsCount }
    , retireCounts_( threadsCount, 0 )
{
    /// Голова всегда указывает на пустой узел.
    tail_ = new Node{ nullptr, nullptr }; ///< Пустой узел для головы.
    head_ = tail_.load(); ///< Голова = хвост, очередь пуста.
} // ctor


template< typename T >
ThreadSafeQueue< T >::~ThreadSafeQueue()
{
    for ( Node* pointer: retireList_ )
    {
        delete pointer;
    }

    Node* node = head_.load();
    while ( node )
    {
        Node* next = node->next.load();
        delete node;
        node = next;
    }
} // dtor


template< typename T >
void ThreadSafeQueue< T >::push( T&& value )
{
    initThreadId();

    Node* newNode   = new Node( std::make_shared< T >( value ), nullptr );
    while ( true ) ///< Попытка добавления узла.
    {
        Node* tailNextCompare = nullptr;
        Node* oldTail = tail_.load();
        /// Установка указателя опасности.
        getHazardPointer( 0 ).store( oldTail );
        if ( oldTail != tail_.load() )
        {
            continue; ///< Другой поток успел изменить хвост, начинаем заново.
        }
        if ( oldTail->next.compare_exchange_weak( tailNextCompare, newNode ) )
        {
            /// Удалось записать в старый хвост указатель на новый элемент.
            /// Пытаемся сдвинуть хвост на новый узел.
            /// Если не выйдет, значит другой поток уже это сделал.
            tail_.compare_exchange_weak( oldTail, newNode );
            break;
        }
        /// Передвигаем указатель на хвост, если другой поток
        /// добавил элемент но не успел сдвинуть хвост.
        tail_.compare_exchange_weak( oldTail, oldTail->next.load() );
    }
    /// Сброс указателя опасности.
    getHazardPointer( 0 ).store( nullptr );
} // push


template< typename T >
std::shared_ptr< T > ThreadSafeQueue< T >::pop()
{
    initThreadId();

    Node* result    = nullptr;
    Node* oldHead   = nullptr;
    while ( true ) ///< Попытка извлечения узла.
    {
        oldHead = head_.load();
        /// Установка указателя опасности.
        getHazardPointer( 0 ).store( oldHead );
        if ( oldHead != head_.load() )
        {
            continue; ///< Другой поток успел изменить голову, начинаем заново.
        }
        Node* tail      = tail_.load();
        Node* headNext  = oldHead->next.load();
        /// Установка указателя опасности.
        getHazardPointer( 1 ).store( headNext );
        if ( oldHead != head_.load() )
        {
            continue; ///< Другой поток успел изменить голову (=> next), начинаем заново.
        }
        if ( headNext == nullptr )
        {
            /// Сброс указателей опасности.
            /// Указатель опасности 1 указывает на nullptr, незачем сбрасывать.
            getHazardPointer( 0 ).store( nullptr );
            return nullptr; ///< Очередь пуста.
        }
        if ( oldHead == tail )
        {
            /// Другой поток добавил узел, но не успел поменять хвост.
            /// Если поменять хвост не удалось, значит это сделал другой поток.
            tail_.compare_exchange_weak( tail, headNext );
            /// Сброс указателей опасности.
            getHazardPointer( 0 ).store( nullptr );
            getHazardPointer( 1 ).store( nullptr );
            continue;
        }
        result = headNext;
        if ( head_.compare_exchange_weak( oldHead, headNext ) )
        {
            break; ///< Удалось сдвинуть голову.
        }
        getHazardPointer( 0 ).store( nullptr );
        getHazardPointer( 1 ).store( nullptr );
    }
    std::shared_ptr< T > data = result->value;
    result->value = nullptr;
    /// Сброс указателей опасности и очистка памяти.
    getHazardPointer( 0 ).store( nullptr );
    getHazardPointer( 1 ).store( nullptr );
    retire( oldHead );
    return data;
} // pop


template< typename T >
void ThreadSafeQueue< T >::initThreadId()
{
    static size_t defaultId = static_cast< size_t >( -1 );
    if ( defaultId == threadId_.load() )
    {
        threadId_.store( threadCounter_++ );
    }
} // initThreadId


template< typename T >
std::atomic< typename ThreadSafeQueue< T >::Node* >& ThreadSafeQueue< T >::getHazardPointer( size_t number )
{
    return hazardPointers_[ hazardPointersPerThread_ * threadId_ + number ];
} // getHazardPointer


template< typename T >
void ThreadSafeQueue< T >::retire( Node* node )
{
    const size_t retireLimit = batchSize_ * hazardPointers_.size();
    size_t& retireCount = retireCounts_[ threadId_ ];
    retireList_[ batchSize_ * threadId_ + retireCount ] = node;
    if ( retireLimit == ++retireCount )
    {
        scan();
    }
} // retireNode


template< typename T >
void ThreadSafeQueue< T >::scan()
{
    size_t newRetireCount = 0;
    std::unordered_set< Node* > hazardPointersSet;

    for ( const auto& hazardPointer: hazardPointers_ )
    {
        Node* pointer = hazardPointer.load();
        if ( pointer )
        {
            hazardPointersSet.insert( pointer );
        }
    }

    for ( size_t i = batchSize_ * threadId_; i < batchSize_ * ( threadId_ + 1 ); ++i )
    {
        Node* pointer = retireList_[ i ];
        retireList_[ i ] = nullptr;
        if ( hazardPointersSet.end() == hazardPointersSet.find( pointer ) )
        {
            delete pointer; ///< Можно удалить узел, так как ни один указатель опасности на него не указывает.
        }
        else
        {
            /// Узел удалить не удалось, возвращаем в очередь на удаление.
            retireList_[ batchSize_ * threadId_ + newRetireCount ] = pointer;
            ++newRetireCount;
        }
    }
    retireCounts_[ threadId_ ] = newRetireCount;
} // scan

}

#endif // THREADS_THREAD_SAFE_QUEUE_HPP
