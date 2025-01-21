#include <stdio.h>
#include "index_last_negative.h"
int index_last_negative(int arr[], int N)
{
    int i;
    int index_l = -1;
    for (i = 0; i < N; i++)
        if (arr[i] < 0)
            index_l = i;
    return index_l;
}
