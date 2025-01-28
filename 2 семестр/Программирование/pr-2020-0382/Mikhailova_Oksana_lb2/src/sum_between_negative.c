#include <stdio.h>
#include <stdlib.h>
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#define N 100

int sum_between_negative (int arr[N], int arr_size){
    int sum = 0;
    int first, last, i;
    first = index_first_negative (arr, arr_size);
    last = index_last_negative (arr, arr_size);

    for (i=first; i<last; i++){
        sum=sum+abs(arr[i]);
    }

    return sum;
}
