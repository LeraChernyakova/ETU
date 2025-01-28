#include <stdio.h>
#include <stdlib.h>

void abs_max(int *numbers, int index, int *max_n, int *ind_max){
  *max_n = numbers[0];
  for(int k=0; k<index;k++){
    if(abs(*max_n) < abs(numbers[k])){
      *max_n = numbers[k];
      *ind_max = k;
    }
  }
}

void abs_min(int *numbers, int index, int *min_n){
  *min_n = numbers[0];
  for(int p=0; p<index; p++){
    if(abs(*min_n) > abs(numbers[p])){
      *min_n = numbers[p];
    }
  }
}

int diff(int *max_n, int *min_n){
  int different = *max_n - *min_n;
  return different;
}

void sum(int *numbers, int index, int *ind_max, int *summa){
  for(int j = *ind_max; j < index; j++){
    *summa = *summa + numbers[j];
  }
}

// ------------------------------------------

int main()
{
    int numbers[100];
    int index = 0;
    int summa = 0;
    int value, max_n, ind_max, min_n, different;

    scanf("%d", &value);

    while(getchar()!='\n'){
        scanf("%d", &numbers[index]);
        index++;
    }
    
    switch(value){
        case 0:
          abs_max(numbers, index, &max_n, &ind_max);
          printf("%d\n", max_n);
          break;
        case 1:
          abs_min(numbers, index, &min_n);
          printf("%d\n", min_n);
          break;
        case 2:
          abs_max(numbers, index, &max_n, &ind_max);
          abs_min(numbers, index, &min_n);
          different = diff(&max_n, &min_n);
          printf("%d\n", different);
          break;
        case 3:
          abs_max(numbers, index, &max_n, &ind_max);
          sum(numbers, index, &ind_max, &summa);
          printf("%d\n", summa);
          break;
        default:
          printf("Данные некорректны\n");
          break;
    }

    return 0;
}
