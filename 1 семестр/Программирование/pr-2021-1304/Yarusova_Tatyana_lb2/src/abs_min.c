#include <stdio.h>
#include <stdlib.h>
#include "abs_min.h"

int abs_min(int arr[100], int index){
    int min = arr[0];
    for(int i = 1; i <= index; i++){
        if (abs(arr[i]) < abs(min)){
        	min = arr[i];
        }
    }
    return min;
}
