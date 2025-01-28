#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
int main (){
int x=0;
int a[100];
int a_size = 0;
char sym = ' ';
int zero,one;
int shto_delat = getchar() - '0';
while(a_size < 100 && sym == ' '){scanf("%d%c",&a[a_size++], &sym);}
switch (shto_delat){
case 0:
zero=index_first_even(a, a_size);
printf ("%d\n", zero);
break;
case 1:
one=index_last_odd (a, a_size);
printf ("%d\n", one);
break;
case 2:
sum_between_even_odd(a, a_size);
break;
case 3:
sum_before_even_and_after_odd(a, a_size);
break;
default:
printf ("Данные некорректны");
}
return 0;
}
