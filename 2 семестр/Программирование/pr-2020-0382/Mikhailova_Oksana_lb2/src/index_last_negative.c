#include <stdio.h>
#include "index_last_negative.h"
#define N 100

int index_last_negative (int arr[N], int arr_size){
    for (int i=(arr_size-1); i>=0; i--){
        if (arr[i]<0){
            return i;
        }
    }
}
