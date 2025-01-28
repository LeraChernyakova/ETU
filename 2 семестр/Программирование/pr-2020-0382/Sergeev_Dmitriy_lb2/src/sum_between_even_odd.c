#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
#include <stdlib.h>
int sum_between_even_odd(int A[], int b)
{
    int f, l, summ = 0;
    f = index_first_even(A, b);
    l = index_last_odd(A, b);
    int i;
    for (i = f; i < l; i++)
    {
        summ = summ +abs(A[i]); 
    }
    return (summ);
}