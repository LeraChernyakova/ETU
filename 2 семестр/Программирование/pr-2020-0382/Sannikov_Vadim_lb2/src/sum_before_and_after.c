#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_before_and_after(int fnumb[], int length){
    int i, sum1=0, sum2=0;
    for (i=0; i < index_first_zero(fnumb, length); i++){
    	sum1+=abs(fnumb[i]);
    }
    for (i = index_last_zero(fnumb, length) + 1; i < length; i++){
    	sum2+=abs(fnumb[i]);
    }
    return sum1 + sum2;
}
