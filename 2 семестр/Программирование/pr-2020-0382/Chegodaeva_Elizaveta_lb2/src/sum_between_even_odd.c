#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_between_even_odd(int arr[], int len){
    int sum=0;
    for (int i=index_first_even(arr, len); i<index_last_odd(arr, len); i++){
        sum=sum+abs(arr[i]);
    }
    return sum;    
}

