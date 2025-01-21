#include "index_last_negative.h"

int index_last_negative(int* arr, int count){
    int i;
    for (i = count-1; i >= 0; i--)
        if (arr[i] < 0) break;
    return i;
    //If i < 0, there aren't negatives.
}
