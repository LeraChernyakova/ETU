#ifndef LOCK_FREE_QUEUE_INL
#define LOCK_FREE_QUEUE_INL

template < typename T >
thread_local std::size_t LockFreeQueue< T >::thread_num_{ std::numeric_limits< std::size_t >::max() };


template < typename T >
LockFreeQueue< T >::LockFreeQueue( std::size_t thread_count ):
     hazard_ptrs_{ thread_count * hp_per_thread_ },
     del_sizes_( thread_count, 0 ),
     del_ptrs_{ batch_ * thread_count * thread_count * hp_per_thread_ },
     curr_thread_num_{ 0 }
{
     Node *dummy = new Node{};   // пустой элемент всегда в голове
     head_.store( dummy, std::memory_order_release );
     tail_.store( dummy, std::memory_order_release );
}


template < typename T >
LockFreeQueue< T >::~LockFreeQueue()
{
     for ( const Node *ptr : del_ptrs_ )
     {
          delete ptr;
     }
     delete_recursive( head_ );
}


template < typename T >
void LockFreeQueue< T >::push( T&& elem )
{
     init_thread_num();
     Node *node = new Node{ elem };
     while ( true )
     {
          Node *comp = nullptr;
          Node *old_tail = tail_.load();
          get_hp( 0 ) = old_tail;
          if ( old_tail != tail_.load() )
          {
               // во время установки указателя опасности изменился tail_
               continue;
          }
          if ( old_tail->next.compare_exchange_weak( comp, node ) )
          {
               // выше добавили элемент, теперь попытка передвинуть tail_.
               // если не получилось, значит, это сделал другой поток и можно ничего не делать
               tail_.compare_exchange_weak( old_tail, node );
               break;
          }
          // если другой поток уже добавил элемент, но не успел передвинуть tail_, то сначала передвинем.
          tail_.compare_exchange_weak( old_tail, old_tail->next.load() );
     }
     get_hp( 0 ) = nullptr;
}


template < typename T >
bool LockFreeQueue< T >::pop( T& elem )
{
     init_thread_num();
     Node *result = nullptr;
     Node *to_delete = nullptr;
     while ( true )
     {
          Node *old_head = head_.load();
          get_hp( 0 ) = old_head;
          if ( old_head != head_.load() )
          {
               // во время установки указателя опасности изменился head_
               continue;
          }
          Node *old_tail = tail_.load();     // можно не защищать его, т.к. нет разыменования
          Node *next = old_head->next.load();
          get_hp( 1 ) = next;
          if ( old_head != head_.load() )
          {
               // во время установки указателя опасности изменился head_ => head_->next тоже
               continue;
          }

          if ( next == nullptr )             // пустая очередь
          {
               get_hp( 0 ) = nullptr;        // get_hp( 1 ) уже nullptr
               return false;
          }
          if ( old_head == old_tail )
          {
               // очередь не пуста, но другой поток не успел передвинуть tail_, делая push.
               // попытка передвинуть tail_, а если не получится, то это уже сделал другой поток
               tail_.compare_exchange_weak( old_tail, next );
          }
          else
          {
               result = next;
               if ( head_.compare_exchange_weak( old_head, next ) )
               {
                    // если получилось, то успешно извлекли элемент,
                    // иначе кто-то другой успел сделать pop, и надо попробовать с новым head_
                    to_delete = old_head;
                    break;
               }
          }
     }
     elem = result->data;
     result->data = T{};      // освобождаем динамическую память, заменяя элементом по умолчанию

     get_hp( 0 ) = nullptr;
     get_hp( 1 ) = nullptr;
     retire( to_delete );
     return true;
}


template < typename T >
void LockFreeQueue< T >::scan()
{
     const std::size_t batch_size = batch_ * del_sizes_.size() * hp_per_thread_;
     std::size_t new_size = 0;
     std::unordered_set< Node * > all_hps;
     for ( const auto& ptr : hazard_ptrs_ )
     {
          all_hps.insert( ptr.load() );
     }

     for ( std::size_t i = thread_num_ * batch_size; i < ( thread_num_ + 1 ) * batch_size; i++ )
     {
          if ( all_hps.find( del_ptrs_[ i ] ) == all_hps.cend() )
          {
               delete del_ptrs_[ i ];
               del_ptrs_[ i ] = nullptr;
          }
          else
          {
               Node *ptr = del_ptrs_[ i ];
               del_ptrs_[ i ] = nullptr;
               del_ptrs_[ thread_num_ * batch_size + new_size ] = ptr;
               ++new_size;
          }
     }
     del_sizes_[ thread_num_ ] = new_size;
}


template < typename T >
void LockFreeQueue< T >::retire( Node *ptr )
{
     const std::size_t batch_size = batch_ * del_sizes_.size() * hp_per_thread_;
     std::size_t& del_count = del_sizes_[ thread_num_ ];
     del_ptrs_[ thread_num_ * batch_size + del_count ] = ptr;
     if ( ++del_count == batch_size )
     {
          scan();
     }
}


template < typename T >
inline void LockFreeQueue< T >::delete_recursive( const typename LockFreeQueue< T >::ANodePtr& ptr )
{
     auto local_ptr = ptr.load( std::memory_order_relaxed );
     if ( local_ptr )
     {
          delete_recursive( local_ptr->next );
          delete local_ptr;
     }
}


template < typename T >
inline void LockFreeQueue< T >::init_thread_num()
{
     if ( thread_num_ == std::numeric_limits< std::size_t >::max() )
     {
          thread_num_ = curr_thread_num_++;
     }
}


template < typename T >
inline typename LockFreeQueue< T >::ANodePtr& LockFreeQueue< T >::get_hp( std::size_t i )
{
     return hazard_ptrs_[ thread_num_ * hp_per_thread_ + i ];
}


#endif // LOCK_FREE_QUEUE_INL
