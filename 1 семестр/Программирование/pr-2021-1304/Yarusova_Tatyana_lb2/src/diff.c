#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"

int diff(int arr[100], int index){
    return (abs_max(arr,index) - abs_min(arr,index));
}
