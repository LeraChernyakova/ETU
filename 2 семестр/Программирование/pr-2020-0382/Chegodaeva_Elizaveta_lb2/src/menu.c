#include <stdio.h>
#include <stdlib.h>
#define N 100
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
int main(){
    int n;
    scanf("%d", &n);
    int arr[N];
    int len=0;
    int i=0;
    char gap= ' ';
    
    while(i<N && gap==' '){
        scanf("%i%c", &arr[i], &gap);
        len=len+1;
        i=i+1;
    } 
    switch (n){
        case 0:
            printf("%d\n",index_first_even(arr,len));
            break;
        case 1:
            printf("%d\n",index_last_odd(arr,len) );
            break;
        case 2:
            printf("%d\n",sum_between_even_odd(arr,len));
            break;
        case 3:
            printf("%d\n",sum_before_even_and_after_odd(arr,len));
            break;
        default: 
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}

