#include "sum_between_even_odd.h"
void sum_between_even_odd(int a[],int n,int f1, int f2)
{
    int i,summa;
    summa=0;
    if (((f1==-1) || (f2==-1)) || (f2-f1<0)){
        printf("Данные некорректны\n");
    }
    else{
        for(i=f1;i<f2;i++){
            summa+=abs(a[i]);
        }
        printf("%d\n",summa);
    }
}
