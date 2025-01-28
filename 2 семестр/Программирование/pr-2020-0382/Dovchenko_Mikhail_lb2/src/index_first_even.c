#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"

int index_first_even(int array[], int size){
    int counter0;
    for(counter0 = 0; counter0 <= size; counter0++)
        if(abs(array[counter0])%2 == 0)
            return counter0;
}