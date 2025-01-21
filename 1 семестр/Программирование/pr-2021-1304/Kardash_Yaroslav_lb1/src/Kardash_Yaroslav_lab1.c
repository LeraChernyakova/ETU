#include <stdio.h>
#include <stdlib.h>
#define N 100
int index_first_zero(int arr[],int n){
int index=0;
for (int i=0;i<n;i++){
if (arr[i]==0){
index=i;
break;}
}
return index;}
int index_last_zero(int arr[],int n){
int index=0;
for (int i=n-1;i>=0;i--){
if (arr[i]==0){
index=i;
break;}
}
return index;
}
int sum_between(int arr[],int n){
int begin = index_first_zero(arr,n);
int end = index_last_zero(arr,n);
int sum =0;
for (int i = begin+1;i<end;i++){
sum+= abs(arr[i]);
}
return sum;
}
int sum_before_and_after(int arr[],int n){
int begin = index_first_zero(arr,n);
int end = index_last_zero(arr,n);
int sum =0;
for (int i = 0;i<begin;i++){
sum+= abs(arr[i]);
}
for (int i =end+1;i<n;i++){
sum+= abs(arr[i]);
}
return sum;
}
int main()
{
int numb_les;
/*printf("Введите номер задания и заполните массив");*/
scanf("%d ",&numb_les);
int arr[N];
int n=0;
char c;
while (n<N){
scanf("%d%c",&arr[n],&c);
n++;
if (c == '\n'){
break;}
}

switch (numb_les){
case 0: {printf("%d\n",index_first_zero(arr,n));
break;}
case 1:{printf("%d\n",index_last_zero(arr,n));
break;}
case 2: {printf("%d\n",sum_between(arr,n));
break;}
case 3: {printf("%d\n",sum_before_and_after(arr,n));
break;}
default: printf("Данные некорректны\n");
}

return 0;
}
