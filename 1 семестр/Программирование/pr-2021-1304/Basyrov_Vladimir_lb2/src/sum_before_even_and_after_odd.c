#include "index_first_even.h"
#include "index_last_odd.h"
#include <stdlib.h>
int sum_before_even_and_after_odd(int s[],int n)
{       int i,start=index_first_even(s,n),finish=index_last_odd(s,n),sum=0;
        for (i=0;i<start;i++)
                sum+=abs(s[i]);
        for (i=finish;i<n;i++)
                sum+=abs(s[i]);
         return sum; }

