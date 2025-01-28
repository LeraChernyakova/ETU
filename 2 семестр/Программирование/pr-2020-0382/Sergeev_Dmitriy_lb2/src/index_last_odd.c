#include "index_last_odd.h"
int index_last_odd(int A[], int b)
{
    b = b - 1;
    while ((A[b] % 2 == 0) && (b >= 0))
    {
        b--;
    }
    return b;
}