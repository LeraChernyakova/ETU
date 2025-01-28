#include "abs_min.h"
#include <stdlib.h>

int abs_min(int numbers[], int quantity){
    int minindex = 0;
    int minnum = abs(numbers[0]);
    for (int i = 1; i < quantity; i++){
        if( abs(numbers[i]) < minnum){
            minnum = abs(numbers[i]);
            minindex = i;
        }
    }

    return minindex;
}
