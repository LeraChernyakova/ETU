#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000

int compare(const void* a, const void* b){
    return *(int*)a - *(int*)b;
}

int findBin(int* arr){
    const int zero = 0;
    return (bsearch(&zero, arr, SIZE, sizeof(int), compare) != NULL);
}

int findBrute(int* arr){
    for(short i = 0; i < SIZE; i++) if(arr[i] == 0) return 1;
    return 0;
}

void stopwatch(int* arr, int (*f)(int*)){
    clock_t time = clock();  
    printf(f(arr) ? "exists\n" : "doesn't exist\n");
    printf("%f\n", ((float)(clock()-time))/CLOCKS_PER_SEC);
}

int main(){
    int arr[SIZE];
    for(short i = 0; i < SIZE; i++) scanf("%d", &arr[i]);
    qsort(arr, SIZE, sizeof(int), compare);
    stopwatch(arr, findBin);
    stopwatch(arr, findBrute);
    return 0;
}