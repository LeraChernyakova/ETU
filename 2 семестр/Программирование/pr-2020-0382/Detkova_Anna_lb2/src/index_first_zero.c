#include "index_first_zero.h"
int index_first_zero(int arr[], int n)
{
    int index, index_first = -1;
    for (index = 0; index < n; index ++) 
    {
        if (arr[index] == 0 && index_first == -1)
            index_first = index;
    }
    return index_first;
}
