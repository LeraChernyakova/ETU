#include <matrix.h>
#include <utils.h>
#if defined( USE_FINE_GRAINED_QUEUE )
#include <fine_grained_queue.h>
#else
#include <thread_safe_queue.h>
#endif

#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <atomic>
#include <iostream>

namespace
{

std::atomic_size_t tasks_done{ 0 };

using Task = std::pair< Matrix, Matrix >;
#if defined( USE_FINE_GRAINED_QUEUE )
using TaskQueue = FineGrainedQueue< Task >;
using MatrixQueue = FineGrainedQueue< Matrix >;
#else
using TaskQueue = ThreadSafeQueue< Task >;
using MatrixQueue = ThreadSafeQueue< Matrix >;
#endif


void produce( size_t tasks_count, size_t size, TaskQueue& tasks )
{
     for ( size_t i = 0; i < tasks_count; i++ )
     {
          tasks.push( { Matrix::generate( size, size ), Matrix::generate( size, size ) } );
     }
}


void consume( size_t tasks_count, TaskQueue& tasks, MatrixQueue& matrices )
{
     auto processor = [ &matrices ]( const Task& task )
     {
          matrices.push( task.first * task.second );
     };
     for ( ; tasks_done < tasks_count; tasks_done++ )
     {
          tasks.process( processor );
     }
     tasks.finish();
}


void output( size_t tasks_count, MatrixQueue& matrices, std::ostream& out )
{
     auto processor = [ &matrices, &out ]( const Matrix& matr )
     {
          out << "RESULT\n" << matr << '\n';
     };
     for ( size_t i = 0; i < tasks_count; i++ )
     {
          matrices.process( processor );
     }
}


} // anonymous namespace

int main( int argc, char *argv[] )
{
     size_t task_count = 0;
     size_t matrix_size = 3;
     size_t producer_count = 1;
     size_t consumer_count = 1;

     if ( argc != 5
          || !str_to_size( argv[ 1 ], producer_count )
          || !str_to_size( argv[ 2 ], consumer_count )
          || !str_to_size( argv[ 3 ], task_count )
          || !str_to_size( argv[ 4 ], matrix_size ) )
     {
          std::cerr << "Usage: " << argv[ 0 ] << " <producer_count> <consumer_count> <task_count> <matrix_size>\n";
          return EXIT_FAILURE;
     }

     std::srand( std::time( nullptr ) );

     TaskQueue tasks;
     MatrixQueue matrices;

     std::vector< std::thread > producers;
     std::vector< std::thread > consumers;
     producers.reserve( producer_count );
     consumers.reserve( consumer_count );

     for ( size_t i = 0; i < producer_count; i++ )
     {
          producers.emplace_back( produce, task_count, matrix_size, std::ref( tasks ) );
     }
     for ( size_t i = 0; i < consumer_count; i++ )
     {
          consumers.emplace_back( consume, task_count * producer_count, std::ref( tasks ), std::ref( matrices ) );
     }
     std::thread printer( output, task_count * producer_count, std::ref( matrices ), std::ref( std::cout ) );


     for ( size_t i = 0; i < producer_count; i++ )
     {
          producers[ i ].join();
     }
     for ( size_t i = 0; i < consumer_count; i++ )
     {
          consumers[ i ].join();
     }
     printer.join();

     return EXIT_SUCCESS;
}


