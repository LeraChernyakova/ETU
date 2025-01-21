#include"index_first_negative.h"
#include"index_last_negative.h"
#include"sum_between_negative.h"

int sum_between_negative(int Data_arr[], int index_first_negative, int index_last_negative){
    int index_arr, sum = 0;
    for(index_arr = index_first_negative; index_arr < index_last_negative; index_arr++){
        if(Data_arr[index_arr] < 0){
            sum = sum - Data_arr[index_arr];
        }else{
            sum = sum + Data_arr[index_arr];
        }
    }

    return sum;
}

