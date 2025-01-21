#include <stdlib.h>
#include <stdio.h>
#define N 100

int size_of_massive(int arr[N], int n){
    int i;
    char c;
    for (i = 0; i < n; i++){
        scanf("%d%c", &arr[i], &c);
        if (c == '\n'){
            break;
        }
    }
    return i+1;
}

int index_first_zero(int arr[N], int n){
    int func_value;
    for(int i = 0; i < n; i++){
        if (arr[i] == 0){
            func_value = i;
        break;
        }
    }
    return func_value;
}

int index_last_zero(int arr[N], int n){
    int func_value;
    for(int i = 0; i < n; i++){
        if (arr[i] == 0){
            func_value = i;
        }
    }
    return func_value;
}

int sum_between(int arr[N], int n){
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

int sum_before_and_after(int arr[N], int n){
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

int main(){
    int value, var_result, arr[N];
    scanf("%d", &value);
    int n = size_of_massive(arr, N);
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
