#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i,k,t,n,f1,f2,f3;
    char c;
    int a[100];
    n=0;
    scanf("%d",&k);
    if (k>3){
        printf("Данные некорректны\n");
        return 0;
    }
    for(i=0;i<100;i++){
        scanf("%d%c", &a[i],&c);
        n++;
        if(c=='\n')
            break;
    }
    f1=index_first_even(a,n);
    f2=index_last_odd(a,n);
    switch(k){
        case 0:
            if(f1!=-1){
                printf("%d\n",f1);
            }
            else{
                printf("Данные некорректны\n");
            }
            break;
        case 1:
            if(f2!=-1){
                printf("%d\n",f2);
            }
            else{
                printf("Данные некорректны\n");
            }
            break;
        case 2:
            sum_between_even_odd(a,n,f1,f2);
            break;
        case 3:
            sum_before_even_and_after_odd(a,n,f1,f2);
            break;
    }
}
