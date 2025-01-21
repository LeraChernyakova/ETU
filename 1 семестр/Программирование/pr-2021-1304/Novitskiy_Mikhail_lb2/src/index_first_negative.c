#include “index_first_negative.h”
int index_first_negative(int* arr,int N){
        int first_i = 0;
        int i;
        for(i = 0; i<N; i++){
                if(arr[i] < 0){
                first_i = i;
                break;
                }
        }
        return(first_i);
}

