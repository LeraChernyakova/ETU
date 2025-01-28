#include <stdio.h>
#include <stdlib.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#define max 100
void sum_between(int num[max], int length)
{
int i=0,sum=0;
for (i = 1 + index_first_zero(num,length); i < index_last_zero(num,length); i++){
sum+=abs(num[i]);
}
printf ("\n%d", sum);
}
