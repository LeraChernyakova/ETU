#include <stdlib.h>
#include "abs_min.h"
int abs_min(int array_size, int array[]){
    int min_index = 0;
    for (int i = 1; i < array_size; i++){
        if (abs(array[i]) < abs(array[min_index])){
            min_index = i;
        }
    }
    return min_index;
}