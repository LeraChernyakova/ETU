#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#define max 100
void sum_before_and_after(int num[max], int length)
{
int i,sum=0;
for (i = 0;i < index_first_zero(num, length); i++){
sum+=abs(num[i]);
}
for (i =1 + index_last_zero(num, length); i < length; i++){
sum+=abs(num[i]);
}
printf ("\n%d", sum);
}
