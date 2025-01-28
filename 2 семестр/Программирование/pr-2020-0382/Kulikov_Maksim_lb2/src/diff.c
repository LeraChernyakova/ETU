#include <stdlib.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"

int diff (int numbers[], int quantity){
    int diff = ( numbers[abs_max(numbers, quantity)] - numbers[abs_min(numbers, quantity)]);
    return diff;
}



