#ifndef THREAD_SAFE_QUEUE_INL
#define THREAD_SAFE_QUEUE_INL

template < typename T >
void ThreadSafeQueue< T >::finish()
{
     std::unique_lock< std::mutex > lock{ mutex_ };
     finish_ = true;
     cond_.notify_all();
}


template < typename T >
void ThreadSafeQueue< T >::push( T&& elem )
{
     {
          std::unique_lock< std::mutex > lock{ mutex_ };
          queue_.push( elem );
     }
     cond_.notify_one();
}


template < typename T >
bool ThreadSafeQueue< T >::process( const std::function< void( const T& ) >& func )
{
     std::pair< bool, T > res;
     res.first = false;
     {
          std::unique_lock< std::mutex > lock{ mutex_ };
          cond_.wait( lock, [ this ](){ return !queue_.empty() || finish_; } );
          if ( !queue_.empty() )
          {
               res = std::make_pair( true, queue_.front() );
               queue_.pop();
          }
     }
     if ( res.first )
     {
          func( res.second );
     }
     return res.first;
}

#endif // THREAD_SAFE_QUEUE_INL
