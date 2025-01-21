#include "index_first_even.h"
int index_first_even(int a[],int n)
{
    int i,k;
    bool flag;
    flag=false;
    k=-1;
    for(i=0;i<n;i++){
        if (abs(a[i])%2==0){
            k=i;
            flag=true;
            break;
        }
    }
    if (flag){
        return k;
    }
    else{
        return -1;
    }
}

