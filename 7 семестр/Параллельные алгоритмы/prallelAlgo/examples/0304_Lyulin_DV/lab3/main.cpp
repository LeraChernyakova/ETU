#include <matrix.h>
#include <utils.h>
#include <lock_free_queue.h>

#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <atomic>
#include <iostream>

namespace
{

std::atomic_size_t tasks_total_consume{ 0 };
std::atomic_size_t tasks_total_out{ 0 };

using Task = std::pair< Matrix, Matrix >;
using TaskQueue = LockFreeQueue< Task >;
using MatrixQueue = LockFreeQueue< Matrix >;


void produce( size_t tasks_count, size_t size, TaskQueue& tasks )
{
     for ( size_t i = 0; i < tasks_count; i++ )
     {
          tasks.push( { Matrix::generate( size, size ), Matrix::generate( size, size ) } );
     }
}


void consume( size_t tasks_count, TaskQueue& tasks, MatrixQueue& matrices )
{
     Task task;
     while ( tasks_total_consume > 0 )
     {
          if ( tasks.pop( task ) )
          {
               --tasks_total_consume;
               matrices.push( task.first * task.second );
          }
     }
}


void output( size_t tasks_count, MatrixQueue& matrices, std::ostream& out )
{
     Matrix matr;
     while ( tasks_total_out > 0 )
     {
          if ( matrices.pop( matr ) )
          {
               --tasks_total_out;
               out << "RESULT\n" << matr << '\n';
          }
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

     TaskQueue tasks( producer_count + consumer_count );
     MatrixQueue matrices( consumer_count + 1 );

     std::vector< std::thread > producers;
     std::vector< std::thread > consumers;
     producers.reserve( producer_count );
     consumers.reserve( consumer_count );
     tasks_total_consume = task_count * producer_count;
     tasks_total_out = task_count * producer_count;

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


