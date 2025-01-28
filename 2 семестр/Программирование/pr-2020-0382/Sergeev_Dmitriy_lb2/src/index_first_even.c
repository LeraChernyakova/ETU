#include "index_first_even.h"
int index_first_even(int A[], int b)
{
    int ind = 0;
    while ((A[ind] % 2 != 0) && (ind != b))
    {
        ind++;
    }
    return ind;
}