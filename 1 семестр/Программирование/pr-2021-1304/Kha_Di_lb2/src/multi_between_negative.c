#include <stdio.h>
#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int a[], int n)
{
    int mb = 1, i;
    for (i = index_first_negative(a, n); i < index_last_negative(a, n); i++) {
        mb *= a[i];
    }

    return mb;
}