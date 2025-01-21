#include "diff.h"
#include "min.h"
#include "max.h"

int diff(int array[], int I){
     int difference, maximum, minimum;
     maximum = max(array, I);
     minimum = min(array, I);
     difference = maximum - minimum;
     return difference;
 }
