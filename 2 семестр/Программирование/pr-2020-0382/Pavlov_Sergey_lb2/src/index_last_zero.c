#include <stdio.h>
#include <stdlib.h>
#include "index_last_zero.h"

int index_last_zero(int array[100], int size){
  int index=size-1;
  while ((array[index]) != 0) index -= 1;
  return index;
}
