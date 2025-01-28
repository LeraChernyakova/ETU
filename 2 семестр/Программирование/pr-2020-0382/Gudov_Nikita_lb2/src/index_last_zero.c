#include "index_last_zero.h"
int index_last_zero(int a[], int size)
{
    int i = 0;
    int lz;


    for (i = 0; i < size; i++)
    {
        if (a[i] == 0)
        {
            lz = i;
        }
    }
    return lz;
}