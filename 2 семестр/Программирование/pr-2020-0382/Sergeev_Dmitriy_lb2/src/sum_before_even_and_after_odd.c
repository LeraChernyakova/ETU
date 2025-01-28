#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#include <stdlib.h>
int sum_before_even_and_after_odd(int A[], int b)
{
    int summ = 0;
    int i;
    for (i = 0; i < b; i++)
    {
          summ = summ + abs(A[i]);
    }
    summ = summ - sum_between_even_odd(A, b);
    return summ;
}