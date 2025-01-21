#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"

int sum_between_negative(int* arr, int count){
    int i, sum = 0;
    for (i = index_first_negative(arr, count); i < index_last_negative(arr, count); i++)
        sum += abs(arr[i]);
    return sum;
    //If there aren't negatives or there's only one, sum = 0.
}
