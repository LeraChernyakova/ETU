#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 1000

void print_arr(int* arr, int max_size){
    for (int i = 0; i < max_size; i++){
        printf("%d ", arr[i]);
    }
}

int* scan_array(int max_size){
    int* scaned_arr;
    scaned_arr = malloc(sizeof(int));

    for (int i = 0; i < max_size; i++){
        scaned_arr = realloc(scaned_arr, sizeof(int)*(i+1));
        scanf("%d", &scaned_arr[i]);
    }

    return scaned_arr;
}

int cmp(const void *i, const void *j)
{
    return *(int *)j - *(int *)i;
}


int main() {
    clock_t start, end;
    start = clock();
    int *array = scan_array(SIZE);
    qsort(array, SIZE, sizeof(int),  (int(*) (const void *, const void *)) cmp);
    end = clock();
    print_arr(array, SIZE);
    //printf("\n0");
    printf("\n%lu", (end - start) / (CLOCKS_PER_SEC));

    return 0;
}
