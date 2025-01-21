#include <stdio.h>
#include "index_first_negative.h"

int index_first_negative(int a[], int n)
{
    int fn = 0, i;
    for (i = n - 1; i >= 0; i--) {
        if (a[i] < 0) {
            fn = i;
            }
    }

    return fn;
}


