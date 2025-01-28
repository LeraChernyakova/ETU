#include <stdio.h>
#include "index_first_negative.h"
int index_first_negative(int arr[], int n){ // n - размер массива
    int i=0;
    for(i;i<n;i++){
        if(arr[i]<0){
            return i;
        }
    }
}
