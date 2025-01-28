#include "sum.h"
#include "abs_max.h"

int sum(int array_size, int array[]){
    int sum = 0;
    for (int i = abs_max(array_size, array); i < array_size; i++)
        sum += array[i];
    return sum;
}
