#include "abs_max.h"

int abs_max(int numbers[], int index){
  int max_n = numbers[0];
  for(int k=0; k<index;k++){
    if(abs(max_n) < abs(numbers[k])){
      max_n = numbers[k];
    }
  }
  return max_n;
}
