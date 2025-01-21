#include "index_last_odd.h"
int index_last_odd(int a[],int n)
{
    int i,k;
    k=-1;
    bool flag;
    flag=false;
    for(i=0;i<n;i++){
        if(abs(a[i])%2==1){
            k=i;
            flag=true;
        }
    }
    if (flag){
        return k;
    }
    else{
        return -1;
    }
}
