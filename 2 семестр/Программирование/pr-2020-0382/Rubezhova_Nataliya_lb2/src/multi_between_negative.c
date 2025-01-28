#include <stdio.h>
#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_between_negative(int arr[],int n){
    int p=1;
    int a=index_first_negative(arr,n);
    int b=index_last_negative(arr,n);
    int i=0;
    for(i=a;i<b;i++)p*=arr[i];
    return p;
}
