#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_before_and_after(int array[100], int size){
  int sum=0;
  int i_last = index_last_zero(array,size);
  int i_first = index_first_zero(array);
  for (int k=0;k<i_first;k++){
    sum += abs(array[k]);
  }
  for (int k=i_last;k<size;k++){
    sum += abs(array[k]);
  }
  return sum;
}
