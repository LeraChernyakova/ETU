#include "index_last_zero.h"
int index_last_zero(int arr[100], int n){
    int func_value;
    for(int i = 0; i < n; i++){
        if (arr[i] == 0){
            func_value = i;
        }
    }
    return func_value;
}
