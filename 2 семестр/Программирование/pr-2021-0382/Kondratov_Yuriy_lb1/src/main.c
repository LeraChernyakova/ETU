#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 1000

int cmp(const void *, const void *);

int main() {
    clock_t time;
    int arr[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++) {
        scanf("%d", &arr[i]);
    }
    time = clock();
    qsort(arr, ARR_SIZE, sizeof(int), cmp);
    time = clock() - time;
    for (int i = 0; i < ARR_SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%f", ((float) time)/CLOCKS_PER_SEC);
    return 0;
}

int cmp(const void *a, const void *b) {
    int* num1 = (int *) a;
    int* num2 = (int *) b;
    if (abs(*num1) > abs(*num2)) return -1;
    else if (abs(*num1) < abs(*num2)) return 1;
    else return 0;
}
