#include "sum.h"
#include "abs_max.h"

int sum(int numbers[], int index){
  int numb = abs_max(numbers, index);
  int summa = 0;
  int key = 0;
  for(int j = 0; j < index; j++){
    if (numbers[j] == numb){
      key = 1;
    }
    if (key==1){
      summa = summa + numbers[j];
    }
  }
  return summa;
}
