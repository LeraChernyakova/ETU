#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_between_negative(int arr[],int size){
    int multi;
    int x=index_first_negative(arr,size);
    int y=index_last_negative(arr,size);
    int i;
    multi=1;
    for(i=x;i<y;i++){
    multi*=arr[i];
    }
    return multi;
}
