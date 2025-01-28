#include <stdio.h>
#include <stdlib.h>
#include "index_last_zero.h"
#define max 100
int index_last_zero(int num[max], int length)
{
int i,last=0;
for (i = 0; i < length; i++)
    {if (num[i]==0) last=i;
    }
return last;
}
