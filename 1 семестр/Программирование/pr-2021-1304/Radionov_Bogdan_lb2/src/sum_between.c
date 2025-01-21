#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_between(int arr[100], int n){
    int d = index_first_zero(arr, n);
    int b = index_last_zero(arr, n);
    int sum = 0;
    int func_value;
    for(int i = d; i < b; i++){
        sum = sum + abs(arr[i]);
    }
    func_value = sum;
    return func_value;
}
