#include <stdio.h>
#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int array[], int size){
    int counter2, sbed = 0;
    for(counter2 = index_first_even(array, size); counter2 < index_last_odd(array, size); counter2++)
        sbed += abs(array[counter2]);
    return sbed;
}