#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
int sum_before_even_and_after_odd(int arr[], int len){
    int summ=0;
    for (int i = 0; i < len; i++){
    summ=summ+abs(arr[i]);
    }
    summ=summ-sum_between_even_odd(arr, len);
    return summ;
}

