#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int cmp(const void* a, const void* b){

    const int *f = (const int*)a;
    const int* s = (const int*)b;
    if (abs(*f) > abs(*s))
        return -1;
    if (abs(*f) < abs(*s))
        return 1;
    return 0;
}

int main(){

    int arr[1000];
    int i;
    clock_t start, end;
    for(i = 0; i < 1000; i++)
        scanf("%d", &arr[i]);
    start = clock();
    qsort(arr, 1000, sizeof(int), cmp);
    end = clock();
    for(i = 0; i < 1000; i++)
        printf("%d ", arr[i]);
    printf("\n");
    printf("%f\n", (float)(end-start)/CLOCKS_PER_SEC);
    return 0;
}
