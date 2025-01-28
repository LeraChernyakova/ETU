#include <stdio.h>
#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_before_and_after_negative(int arr[],int n){
    int p=1;
    int a=index_first_negative(arr,n);
    int b=index_last_negative(arr,n);
    int i=0;
    for(i;i<a;i++)p*=arr[i];
    for(i=b;i<n;i++)p*=arr[i];
    return p;
}
