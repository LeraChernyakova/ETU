#include"index_first_negative.h"

int index_first_negative(int Data_arr[], int n){
    int i;
    for(i = 0; i < n; i++){
        if (Data_arr[i] < 0){
            return i;
        }
    }
}

