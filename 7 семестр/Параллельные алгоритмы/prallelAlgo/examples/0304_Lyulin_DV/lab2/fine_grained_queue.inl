#ifndef FINE_GRAINED_QUEUE_INL
#define FINE_GRAINED_QUEUE_INL

template < typename T >
FineGrainedQueue< T >::FineGrainedQueue():
     finish_{ false }
{
     // сделать пустой элемент для различия начала и конца
     front_ = std::make_unique< Node >();
     back_ = front_.get();
}


template < typename T >
void FineGrainedQueue< T >::finish()
{
     std::unique_lock< std::mutex > lock{ front_mutex_ };
     finish_ = true;
     cond_.notify_all();
}


template < typename T >
void FineGrainedQueue< T >::push( T&& elem )
{
     std::unique_lock< std::mutex > lock{ back_mutex_ };
     back_->next = std::make_unique< Node >();
     back_->data = elem;
     back_ = back_->next.get();
     cond_.notify_one();
}


template < typename T >
bool FineGrainedQueue< T >::process( const std::function< void( const T& ) >& func )
{
     std::pair< bool, T > res;
     res.first = false;
     bool empty = true;
     auto is_end = [ this ]()
     {
          return front_.get() != get_back_locked() || finish_;
     };
     {
          std::unique_lock< std::mutex > lock{ front_mutex_ };
          cond_.wait( lock, is_end );
          if ( finish_ )
          {
               return false;
          }
          res = std::make_pair( true, front_->data );
          front_ = std::move( front_->next );     // pop
     }
     if ( res.first )
     {
          func( res.second );
     }
     return res.first;
}


template < typename T >
const typename FineGrainedQueue< T >::Node *FineGrainedQueue< T >::get_back_locked()
{
     std::unique_lock< std::mutex > lock{ back_mutex_ };
     return back_;
}


#endif // FINE_GRAINED_QUEUE_INL
