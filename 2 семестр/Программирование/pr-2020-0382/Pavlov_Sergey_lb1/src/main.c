#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int array[100]){
  int index=0;
  while ((array[index]) != 0) index += 1;
  return index;
}

int index_last_zero(int array[100], int size){
  int index=size-1;
  while ((array[index]) != 0) index -= 1;
  return index;
}

int sum_between(int array[100], int size){
  int last_zero = index_last_zero(array,size);
  int i = index_first_zero(array);
  int sum=0;
    for (;i<=last_zero; i++){
      sum += abs(array[i]);
    }
  return sum;
}

int sum_before_and_after(int array[100], int size){
  int sum;
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
