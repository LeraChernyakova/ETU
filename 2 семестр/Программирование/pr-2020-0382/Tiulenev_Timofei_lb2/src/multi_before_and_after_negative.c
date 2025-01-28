#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_before_and_after_negative(int arr[],int size){
    int multi=1;
    int x=index_first_negative(arr,size);
    int y=index_last_negative(arr,size);
    int i=0;
    for(i;i<x;i++){
    multi*=arr[i];
    }
    for(i=y;i<size;i++){
    multi*=arr[i];
    }
    return multi;
}
