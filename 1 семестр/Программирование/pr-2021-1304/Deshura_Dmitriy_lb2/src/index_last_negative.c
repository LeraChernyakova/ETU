#include"index_last_negative.h"

int index_last_negative(int Data_arr[], int n){
    int i, result;
    for(i = 0; i < n; i++){
        if (Data_arr[i] < 0){
            result = i;
        }
    }
    return result;
}

