#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"

int sum_before_and_after_negative(int* arr, int count){
    int i, sum = 0;
    for (i = 0; i < count; i++)
        if (i < index_first_negative(arr, count) || i >= index_last_negative(arr, count))
            sum += abs(arr[i]);
    return sum;
    //If there aren't negatives or there's only one, return sum of absolute values all array elements.
}
