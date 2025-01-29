#include <iostream>

#include "threads/tasks.h"

int main( int argc, char **argv )
{
    if ( argc != 2 )
    {
        std::cerr << "Usage: ./threads-extended {threads-count}\n";
        return 1;
    }
    threads::Tasks tasks( std::stoull( argv[1], nullptr, 10 ) );
    if ( !tasks.isValid() )
    {
        std::cerr << "Tasks failed\n";
        return 1;
    }
    return 0;
}