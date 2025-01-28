#include <stdio.h>
#include "index_last_negative.h"
int index_last_negative(int arr[], int n){
    int i=0;
    for(i=n-1;i>=0;i--){
        if(arr[i]<0){
            return i;
        }
    }
}
