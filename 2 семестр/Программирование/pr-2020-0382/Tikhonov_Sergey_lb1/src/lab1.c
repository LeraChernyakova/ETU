#include <stdio.h>
#include <stdlib.h>
int index_first_even(int a[100],int a_size){
for (int x=0; x<a_size; x++){
if(a[x]%2==0){
return x;
}
}
}
int index_last_odd (int a[100], int a_size){
for (int x=(a_size-1); x>=0; x--){
if (a[x]%2!=0){
return x;
}
}
}
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
