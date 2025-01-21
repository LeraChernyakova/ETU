#include "sum_between.h"
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"


int sum_between(int values[], int act, int size){  

    int first = index_first_zero(values, act, size);  

    int last = index_last_zero(values, act, size);  

    int sum = 0;  

  
    for(int i = first; i < last; i++){  

        sum += abs(values[i]);  

    }  

    return sum;  

  

}  
