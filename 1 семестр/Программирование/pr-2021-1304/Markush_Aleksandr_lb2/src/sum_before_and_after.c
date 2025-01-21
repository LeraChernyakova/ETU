#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_before_and_after.h"
#include "sum_between.h"


int sum_before_and_after(int values[], int act, int size){  

    int all_sum = 0;  


    for(int i = 0; i < size; i++){  

        all_sum += abs(values[i]);  

    }  

    int sum;  

    sum = all_sum - sum_between(values, act, size);  

    return sum;

}  
