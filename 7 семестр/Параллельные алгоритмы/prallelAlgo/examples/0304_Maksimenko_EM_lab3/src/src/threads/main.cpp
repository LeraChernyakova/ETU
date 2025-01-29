#include <iostream>

#include "threads/tasks.h"
#include "threads/thread_factory.hpp"
#include <atomic>

constexpr size_t producersDefault = 2;
constexpr size_t consumersDefault = 6;
constexpr size_t tasksDefault = 30000;

int main( int argc, char** argv )
{
    size_t producers = producersDefault;
    size_t consumers = consumersDefault;
    size_t tasks = tasksDefault;

    try
    {
        if ( argc > 1 )
        {
            producers = std::stoull( argv[ 1 ], nullptr, 10 );
        }
        if ( argc > 2 )
        {
            consumers = std::stoull( argv[ 2 ], nullptr, 10 );
        }
        if ( argc > 3 )
        {
            tasks = std::stoull( argv[ 3 ], nullptr, 10 );
        }
    }
    catch ( std::exception& )
    {
        std::cerr << "Invalid argument\n";
        return 1;
    }
    
    if ( argc > 4 )
    {
        std::cerr << "Usage: threading [producers] [consumers] [tasks]\n";
        return 1;
    }

    threads::ThreadFactory< threads::TaskGen > generationFactory(
          producers
        , consumers
        , tasks
        , &threads::Tasks::generateMatrices
        , &threads::Tasks::multiplyMatricesSerial
    );
    generationFactory.wait();
    return 0;
}
