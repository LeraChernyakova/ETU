#include "index_first_zero.h"
int index_first_zero(int arr[100], int n){
    int func_value;
    for(int i = 0; i < n; i++){
        if (arr[i] == 0){
            func_value = i;
        break;
        }
    }
    return func_value;
}
