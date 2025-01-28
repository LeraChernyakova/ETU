#include "sum_before_and_after.h"
int sum_before_and_after(int arr[], int n)
{
    int ind_first, ind_last, sum = 0, item;
    ind_first = index_first_zero(arr, n);
    ind_last = index_last_zero(arr, n);
    if (ind_first == -1 && ind_last == 100) 
        return -1;
    for (item = 0; item <= ind_first; item ++)
    {
        sum = sum + abs(arr[item]);
    }
    for (item = ind_last; item < n; item ++)
        sum = sum + abs(arr[item]);
    return sum;    
}
