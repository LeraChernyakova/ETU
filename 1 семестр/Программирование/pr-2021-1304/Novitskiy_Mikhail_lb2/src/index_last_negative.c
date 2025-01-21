#include “index_last_negative.h”

int index_last_negative(int* arr,int N){
        int last_i = 0;
        int i;
        for(i = N-1;i>=0; i--){
                if(arr[i] < 0){
                last_i = i;
                break;
                }
        }
        return(last_i);
}

