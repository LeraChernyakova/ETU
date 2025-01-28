#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define arr_size 1000

float bubble_sort(int* array){
  clock_t start = clock();
  for (int i=0;i < arr_size-1; i++){
    for (int j=0; j<arr_size-1 ; j++){
      int tmp;
      if (array[j] > array[j+1]){

        tmp = array[j];
        array[j] = array[j+1];
        array[j+1] = tmp; 
      }

    }
  }
  clock_t end = clock();
  return ((float)(end - start) / CLOCKS_PER_SEC);
}

int qsort_compare(const void *pa, const void *pb){

    const int *p1 = pa;
    const int *p2 = pb;
    return (*p1 - *p2);
}

void print_arr(int* array){

  int i=0;

  while(i<arr_size){

    printf("%d ", array[i]);
    i++;
  }
  printf("\n");
}


int main(){

  float horal_1,horal_2;

  int array[arr_size];
  int array_2[arr_size];
  int size=0;

  while (size<arr_size){

    scanf("%d", &array[size]);
    array_2[size] = array[size];
    size++;
  }


  horal_1 = bubble_sort(array);

  clock_t start = clock();

  qsort(array_2, arr_size, sizeof(int), qsort_compare);

  clock_t end = clock();

  horal_2 = (float) (end-start)/ CLOCKS_PER_SEC;

  // Вывод
  print_arr(array);
  printf("%f\n", horal_1);
  printf("%f\n", horal_2);
  return 0;
}
