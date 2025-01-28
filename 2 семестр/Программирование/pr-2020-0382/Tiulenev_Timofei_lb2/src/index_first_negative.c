#include "index_first_negative.h"
int index_first_negative(int arr[], int size){
    int i;
    for(i=0;i<size;i++){
        if(arr[i]<0){
            return i;
        }
    }
}
