#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"

int index_first_zero(int array[100]){
  int index=0;
  while ((array[index]) != 0) index += 1;
  return index;
}
