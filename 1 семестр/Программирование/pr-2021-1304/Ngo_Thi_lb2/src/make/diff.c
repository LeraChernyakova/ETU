#include "diff.h"
int diff(int arr[], int size)
{
    return(abs_max(arr, size) - abs_min(arr,size));
}
 
