#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main(){

  int command;
  int array[100], size=0, index=0;

  scanf("%d", &command);

  while ((index < 100)&&(getchar() != '\n')){
    scanf("%d,", &array[size]);
    size += 1;
    index += 1;
  }

  switch (command) {
    case 0: printf("%d\n", index_first_zero(array));
      break;
    case 1: printf("%d\n", index_last_zero(array,size));
      break;
    case 2: printf("%d\n", sum_between(array,size));
      break;
    case 3: printf("%d\n", sum_before_and_after(array,size));
      break;
    default: printf("Данные некорректны\n");
      break;
  }
  return 0;
}
