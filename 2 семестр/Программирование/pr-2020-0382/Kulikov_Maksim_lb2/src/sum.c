#include <stdlib.h>
#include "sum.h"
#include "abs_max.h"

int sum (int numbers[], int quantity){
    int sum = 0;
    for(int i = abs_max(numbers, quantity); i < quantity; i++){
        sum += numbers[i];
    }
    return sum;
}
