#include "index_last_negative.h"

int index_last_negative(int arr[], int count){
    int indx;
    for (int i = count - 1; i >= 0; --i){
        if (arr[i] < 0){
            indx = i;
            break;
        }
    }
    return indx;
}