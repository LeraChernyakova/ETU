#include "sum_between_even_odd.h"
#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_between_even_odd(int a[100], int a_size){
int sum=0;
int first, last, x;
first = index_first_even(a, a_size);
last=index_last_odd (a, a_size);
for (x=first; x<last; x++){
sum=sum+abs(a[x]);
}
printf ("%d\n", sum);
}
