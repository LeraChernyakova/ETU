#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_between(int a[], int size)
{
    int s = 0;
    int c = index_first_zero(a, size);
    int b = index_last_zero(a, size)+1;
    for ( int i = c; i < b; i++)
    {
        s = s + abs(a[i]);
    }
    return s;
}