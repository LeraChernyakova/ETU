#include "index_last_odd.h"
#include "index_first_even.h"
#include "sum_before_even_and_after_odd.h"
#include <stdio.h>
#include <stdlib.h>
int sum_before_even_and_after_odd(int a[100], int a_size){
int sum=0;
int first, last, x;
first=index_first_even(a, a_size);
last=index_last_odd (a, a_size);
for (x=0; x<first; x++){
sum=sum+abs(a[x]);
}
for (x=last; x<a_size; x++){
sum=sum+abs(a[x]);
}
printf ("%d\n", sum);
}
