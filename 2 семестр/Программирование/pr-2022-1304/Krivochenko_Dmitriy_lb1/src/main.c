#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000

int cmp(const void * a,
  const void * b) {
  const int * f = (int * ) a;
  const int * s = (int * ) b;
  if ( * f > * s)
    return 1;
  if ( * f < * s)
    return -1;
  return 0;

}

int main() {

  int arr_qsort[N];
  int arr_bubble[N];
  int q;
  for (int i = 0; i < N; i++) {
    scanf("%d", & arr_qsort[i]);
    arr_bubble[i] = arr_qsort[i];
  }

  clock_t time_start_bubble = clock();
  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < N - i - 1; j++) {
      if (arr_bubble[j] > arr_bubble[j + 1]) {
        q = arr_bubble[j];
        arr_bubble[j] = arr_bubble[j + 1];
        arr_bubble[j + 1] = q;
      }
    }
  }
  clock_t time_end_bubble = clock() - time_start_bubble;

  for (int i = 0; i < N; i++) {
    printf("%d ", arr_bubble[i]);
  }
  puts("");

  clock_t time_start_qsort = clock();
  qsort(arr_qsort, N, sizeof(int), cmp);
  clock_t time_end_qsort = clock() - time_start_qsort;
  printf("%f\n", ((float) time_end_bubble) / CLOCKS_PER_SEC);
  printf("%f\n", ((float) time_end_qsort) / CLOCKS_PER_SEC);
  return 0;

}
