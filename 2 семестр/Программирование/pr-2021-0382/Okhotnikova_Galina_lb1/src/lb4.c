#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define C 1000

int compfunction1(const void* a1, const void* a2){
    return abs(*(int*)a1) <= abs(*(int*)a2);
}

int main() {
    int i;
    int arr[C];
    for (i = 0; i < C; i++) {
        scanf("%d", &arr[i]);
    }
    clock_t start_time;
    start_time = clock();
    qsort(arr, C, sizeof(int), (int(*)(const void*, const void*))compfunction1);
    clock_t end_time;
    end_time = clock() - start_time;
    for (i = 0; i < C; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n%f", (double)end_time/CLOCKS_PER_SEC);
    return 0;
}
