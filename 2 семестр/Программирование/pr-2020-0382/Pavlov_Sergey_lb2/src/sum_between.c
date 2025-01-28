#include <stdio.h>
#include <stdlib.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"


int sum_between(int array[100], int size){
  int last_zero = index_last_zero(array,size);
  int i = index_first_zero(array);
  int sum=0;
    for (;i<=last_zero; i++){
      sum += abs(array[i]);
    }
  return sum;
}
