#include "abs_min.h"

int abs_min(int numbers[], int index){
  int min_n = numbers[0];
  for(int p=0; p<index; p++){
    if(abs(min_n) > abs(numbers[p])){
      min_n = numbers[p];
    }
  }
  return min_n;
}
