#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[], int count){
    int result = 1, first_negative = index_first_negative(arr, count), last_negative = index_last_negative(arr, count);
    for(int i = first_negative; i < last_negative; ++i){
        result *= arr[i];
    }
    return result;
}