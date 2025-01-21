#include "index_first_negative.h"

int index_first_negative(int arr[], int count){
    int indx;
    for (int i = 0; i < count; ++i){
        if (arr[i] < 0){
            indx = i;
            break;
        }
    }
    return indx;
}