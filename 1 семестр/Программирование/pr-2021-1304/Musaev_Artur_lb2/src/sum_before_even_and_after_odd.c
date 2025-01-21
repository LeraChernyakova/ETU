#include "sum_before_even_and_after_odd.h"
void sum_before_even_and_after_odd(int a[],int n,int f1, int f2){
    int i,summa=0,ans=0;
    if (f1!=-1){
        for(i=0;i<f1;i++){
            summa+=abs(a[i]);
        }
    }
    if (f2!=-1){
        for(i=f2;i<n;i++){
            summa+=abs(a[i]);
        }
    }
    if ((f1==-1) && (f2==-1)){
        printf("Данные некорректны\n");
    }
    else if (f2-f1<0){
        for(i=0;i<n;i++){
            ans+=abs(a[i]);
        }
        printf("%d\n",ans);
    }
    else{
    printf("%d\n",summa);}
}
