#include <stdio.h>
#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int a[], int n)
{
    int mba = 1, i;
    for (i = 0; i < index_first_negative(a, n); i++) {
        mba *= a[i];
    }
    for (i = index_last_negative(a, n); i < n; i++) {
        mba *= a[i];
    }

    return mba;
}