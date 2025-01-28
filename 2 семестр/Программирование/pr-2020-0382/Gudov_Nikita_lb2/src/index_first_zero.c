#include "index_first_zero.h"
int index_first_zero(int a[], int size)
{
    int i, fz;

    for (i = 0; i < size; i++)
    {
        if (a[i] == 0)
        {
            fz = i;
            break;
        }
    }
    return fz;
}