#include "diff.h"
#include "abs_max.h"
#include "abs_min.h"

int diff(int numbers[], int index){
  int different = abs_max(numbers, index) - abs_min(numbers, index);
  return different;
}
