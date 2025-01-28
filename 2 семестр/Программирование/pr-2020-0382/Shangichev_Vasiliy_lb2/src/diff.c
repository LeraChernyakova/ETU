#include "max.h"
#include "min.h"

int diff(int arr[], int size){
    int diff;
    diff = max(arr, size) - min(arr, size);
    return diff;
}