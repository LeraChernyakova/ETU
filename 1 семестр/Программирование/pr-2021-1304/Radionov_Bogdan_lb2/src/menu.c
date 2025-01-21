#include <stdio.h>
#include <stdlib.h>
#include "size_of_massive.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
int main(){
    int value, var_result, arr[100];
    scanf("%d", &value);
    int n = size_of_massive(arr, 100);
    switch (value) {
        case (0):
            var_result = index_first_zero(arr, n);
            break;
        case (1):
            var_result = index_last_zero(arr, n);
            break;
        case (2):
            var_result = sum_between(arr, n);
            break;
        case (3):
            var_result = sum_before_and_after(arr, n);
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    if ((value >= 0) && (value <= 3)){
        printf("%d\n", var_result);
    }
}
