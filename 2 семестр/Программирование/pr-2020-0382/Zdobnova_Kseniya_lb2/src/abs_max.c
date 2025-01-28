#include <stdlib.h>
#include "abs_max.h"
int abs_max(int array_size, int array[]){
    int max_index = 0;
    for (int i = 1; i < array_size; i++){
        if (abs(array[i]) > abs(array[max_index])){
            max_index = i;
        }
    }
    return max_index;
}