#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_before_and_after(int a[], int size)
{
    int s = 0;
    int c = index_first_zero(a, size);
    int b = index_last_zero(a, size);
    for(int i = 0; i < c; i++)
    {
        s = s + abs(a[i]);
    }
    for(int i = b; i < size; i++)
    {
        s = s + abs(a[i]);
    }
    return s;
}