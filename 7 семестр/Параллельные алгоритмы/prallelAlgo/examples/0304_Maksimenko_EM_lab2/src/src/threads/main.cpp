#include <iostream>

#include "threads/tasks.h"
#include "threads/thread_factory.hpp"

constexpr size_t threadsCountDefault = 1;
constexpr size_t producersDefault = 2;
constexpr size_t consumersDefault = 6;
constexpr size_t tasksDefault = 30000;

int main( int argc, char** argv )
{
    size_t threadsCount = threadsCountDefault;
    size_t producers = producersDefault;
    size_t consumers = consumersDefault;
    size_t tasks = tasksDefault;

    try
    {
        if ( argc > 1 )
        {
            threadsCount = std::stoull( argv[ 1 ], nullptr, 10 );
        }
        if ( argc > 2 )
        {
            producers = std::stoull( argv[ 2 ], nullptr, 10 );
        }
        if ( argc > 3 )
        {
            consumers = std::stoull( argv[ 3 ], nullptr, 10 );
        }
        if ( argc > 4 )
        {
            tasks = std::stoull( argv[ 4 ], nullptr, 10 );
        }
    }
    catch ( std::exception& )
    {
        std::cerr << "Invalid argument\n";
        return 1;
    }
    
    if ( argc > 5 )
    {
        std::cerr << "Usage: threading [thread-count] [producers] [consumers] [tasks]\n";
        return 1;
    }
    const size_t tasksPerProducer = tasks / producers;
    const size_t tasksPerConsumer = tasks / consumers;
    if ( tasksPerProducer * producers != tasksPerConsumer * consumers 
      || tasksPerConsumer * consumers != tasks )
    {
        std::cerr << "Invalid tasks per producers/consumers count\n";
        return 1;
    }

    threads::ThreadFactory< threads::TaskGen > generationFactory;
    threads::ThreadFactory< threads::TaskOut > outputFactory;

    for ( size_t i = 0; i < producers; ++i )
    {
        generationFactory.addProducer( &threads::Tasks::generateMatrices, tasksPerProducer );
    }
    for ( size_t i = 0; i < consumers; ++i )
    {
        if ( threadsCount == 1 )
        {
            generationFactory.addConsumer( std::bind( 
                &threads::Tasks::multiplyMatricesSerial
                , std::placeholders::_1, std::ref( outputFactory ) ), tasksPerConsumer );
        }
        else
        {
            generationFactory.addConsumer( std::bind( 
                &threads::Tasks::multiplyMatricesParallel
                , std::placeholders::_1, std::ref( outputFactory ), threadsCount ), tasksPerConsumer );
        }
    }
    outputFactory.addConsumer( &threads::Tasks::writeResultMatrix, tasks );

    generationFactory.wait();
    outputFactory.wait();
    return 0;
}
