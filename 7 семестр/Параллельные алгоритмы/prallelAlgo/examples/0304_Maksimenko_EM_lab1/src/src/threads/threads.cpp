#include <iostream>

#include "threads/tasks.h"

int main()
{
    threads::Tasks tasks( 1 );
    if ( !tasks.isValid() )
    {
        std::cerr << "Tasks failed\n";
        return 1;
    }
    return 0;
}