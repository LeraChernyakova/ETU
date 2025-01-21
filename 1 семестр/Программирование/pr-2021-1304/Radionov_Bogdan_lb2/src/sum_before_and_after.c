#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_before_and_after(int arr[100], int n){
    int sum1 = 0;
    int sum2 = 0;
    int d, b, func_value;
    d = index_first_zero(arr, n);
    b = index_last_zero(arr, n);
    for(int i = 0; i < d; i++){
        sum1 = sum1 + abs(arr[i]);
    }
    for(int i = b; i < n; i++){
        sum2 = sum2 + abs(arr[i]);
    }
    func_value = sum1 + sum2;
    return func_value;
}
