#include <stdio.h>
#include <stdlib.h>
#include "index_last_odd.h"

int index_last_odd(int array[], int size){
    int counter1;
    for(counter1 = size-1; counter1 >= 0; counter1--)
        if(abs(array[counter1])%2 == 1)
            return counter1;
}