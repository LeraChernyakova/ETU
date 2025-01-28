#include "index_last_zero.h"
int index_last_zero(int arr[], int n)
{
    int index, index_last = 100;
    for (index = 0; index < n; index ++) 
    {
        if (arr[index] == 0)
            index_last = index;
    }
    return index_last;
} 
