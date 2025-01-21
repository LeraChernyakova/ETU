#include <stdio.h>
#include "index_last_negative.h"

int index_last_negative(int a[], int n)
{
    int ln = n - 1, i;
    for (i = 0; i < n; i++) {
        if (a[i] < 0) {
            ln = i;
            }
    }

    return ln;
}