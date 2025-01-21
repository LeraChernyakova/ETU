#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include “sum_before_and_after_negative.h”

int sum_before_and_after_negative(int* arr,int N){
        int sum = 0;
        int i;
        for(i = 0;i <index_first_negative(arr,N);i++){
                sum += abs(arr[i]);
        }
        for(i = index_last_negative(arr,N);i<N;i++){
                sum += abs(arr[i]);
        }
        return(sum);
}

