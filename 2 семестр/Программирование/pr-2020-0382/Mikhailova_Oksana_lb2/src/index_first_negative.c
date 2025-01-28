#include <stdio.h>
#include "index_first_negative.h"
#define N 100

int index_first_negative (int arr[N], int arr_size){
    for (int i=0; i<arr_size; i++){
        if (arr[i]<0){
            return i;
        }
    }
}
