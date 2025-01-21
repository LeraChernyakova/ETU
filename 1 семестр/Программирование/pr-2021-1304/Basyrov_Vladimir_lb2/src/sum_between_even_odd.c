#include "index_first_even.h"
#include "index_last_odd.h"
#include <stdlib.h>

int  sum_between_even_odd(int s[],int n)
{       int i,start=index_first_even(s,n),finish=index_last_odd(s,n),sum=0;
        for (i=start;i<finish;i++)
                sum+=abs(s[i];
        return sum;}
