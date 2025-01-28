#include <stdio.h>
#include <stdlib.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_between(int fnumb[], int length){
    int i,sum=0;
    for (i = index_first_zero(fnumb, length) + 1; i < index_last_zero(fnumb, length); i++){
    sum+=abs(fnumb[i]);
    }
    return sum;
}
