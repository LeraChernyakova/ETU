#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int array[], int index){
    int difference;
    difference = max(array, index) - min(array, index);
    return difference;
}

