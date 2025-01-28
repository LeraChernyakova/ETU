#include "abs_max.h"
#include <stdlib.h>

int abs_max(int numbers[], int quantity){
    int maxnum = abs(numbers[0]);
    int maxindex = 0;
    for (int i = 1; i < quantity; i++){
        if( abs(numbers[i]) > abs(maxnum)){
            maxnum = abs(numbers[i]);
            maxindex = i;
        }
    }

    return maxindex;
}