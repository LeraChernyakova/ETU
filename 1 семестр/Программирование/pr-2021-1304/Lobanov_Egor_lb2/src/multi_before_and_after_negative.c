#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int count){
    int result = 1, first_negative = index_first_negative(arr, count), last_negative = index_last_negative(arr, count);
    for(int i = 0; i < first_negative; ++i){
        result *= arr[i];
    }
    for(int i = last_negative; i < count; ++i){
        result *= arr[i];
    }
    return result;
}