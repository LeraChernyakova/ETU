#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_between_negative(int* arr,int N){
        int sum = 0;
        int i;
        for(i = index_first_negative(arr,N); i < index_last_negative(arr,N); i++){
                sum += abs(arr[i]);
        }
        return(sum);
}

