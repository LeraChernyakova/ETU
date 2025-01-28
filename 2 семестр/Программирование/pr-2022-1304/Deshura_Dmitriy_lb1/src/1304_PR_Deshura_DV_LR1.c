#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000

int cmp(const void * x1, const void * x2){
    if(*(int*)x1 > *(int*)x2)
        return 1;
    if(*(int*)x1 == *(int*)x2)
        return 0;
    if(*(int*)x1 < *(int*)x2)
        return -1;
}

int main(){
    int arr[SIZE], zero = 0;
    float start, end;
    for(int i = 0; i <= (SIZE - 1); i++)
        scanf("%d", &arr[i]);
    qsort(arr, SIZE, sizeof(int), cmp);
    
    start = clock();
    int *pointer = bsearch(&zero, arr, SIZE, sizeof(int), cmp);
    end = clock();
    if(pointer == NULL)
        printf("doesn't exist\n");
    else
        printf("exists\n");
    printf("%f\n", (end - start)/CLOCKS_PER_SEC);

    int i = 0;
    start = clock();
    while(arr[i] != 0 && i < SIZE)
        i++;
    end = clock();
    if(i == SIZE)
        printf("doesn't exist\n");
    else
        printf("exists\n");
    printf("%f\n", (end - start)/CLOCKS_PER_SEC);
    
    return 0;
}
