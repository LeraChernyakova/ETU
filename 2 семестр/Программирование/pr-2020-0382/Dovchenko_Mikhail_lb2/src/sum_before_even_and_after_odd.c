#include <stdio.h>
#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int array[], int size){
    int counter3, counter4, sbeaao = 0;
    for(counter3 = index_first_even(array, size) - 1;  counter3 >= 0;  counter3--)
        sbeaao += abs(array[counter3]);
    for(counter4 = index_last_odd(array, size); counter4 < size; counter4++)
        sbeaao += abs(array[counter4]);
    return sbeaao;
}