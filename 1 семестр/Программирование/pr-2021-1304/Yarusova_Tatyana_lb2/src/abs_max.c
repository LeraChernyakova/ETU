#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"

int abs_max(int arr[100],int index){
    int max = abs(arr[0]);
    for(int i = 1; i <= index; i++){
        if (abs(arr[i]) > abs(max)){ 
                                max = arr[i];
        }
    }
    return max;
}
