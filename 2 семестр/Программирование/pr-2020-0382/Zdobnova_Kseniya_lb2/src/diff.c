#include "diff.h"
#include "abs_max.h"
#include "abs_min.h"
int diff(int array_size, int array[]){
    return (array[abs_max(array_size, array)] - array[abs_min(array_size, array)]);
}
