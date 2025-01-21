#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
int multi_between_negative(int arr[], int N, int *err)
{
    int i;
    int res = 1;
    int index_f = index_first_negative(arr, N);
    int index_l = index_last_negative(arr, N);
    if ((index_f == index_l) || (index_f < 0) || (index_l < 0))
    {
        *err = 1;
        return 0;
    }
    for (i = index_f; i < index_l; i++)
        res *= arr[i];
    return res;
}
