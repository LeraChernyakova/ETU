#include "min.h"

int sum(int arr[], int size){
    int minimum = min(arr, size);
    int sum = 0;
    int i;
    for (i = 0; i < size; i++){
        if (arr[i] != minimum){
            sum += arr[i];
        }
        else {
            break;
        }
    }
    return sum;
}
