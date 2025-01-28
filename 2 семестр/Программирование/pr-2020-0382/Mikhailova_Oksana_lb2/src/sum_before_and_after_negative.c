#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#define N 100

int sum_before_and_after_negative (int arr[N], int arr_size){
    int sum = 0;
    int first, last, i;
    first = index_first_negative (arr, arr_size);
    last = index_last_negative (arr, arr_size);

    for (i=0; i<first; i++){
        sum=sum+abs(arr[i]);
    }

    for (i=last; i<arr_size; i++){
        sum=sum+abs(arr[i]);
    }

    return sum;

}
