#include "index_first_negative.h"

int index_first_negative(int* arr, int count){
    int i;
    for (i = 0; i < count; i++)
        if (arr[i] < 0) break;
    return i;
    //If i = count, there aren't negatives.
}
