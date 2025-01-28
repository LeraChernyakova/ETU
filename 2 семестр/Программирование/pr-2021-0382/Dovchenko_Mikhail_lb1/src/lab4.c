#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000

int compare(const void*, const void*);

int main(){
    int arr[N];
    int zero = 0;
    int flag = 0;
    clock_t start_b, end_b, start_c, end_c;

    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    start_b = clock();
    qsort(arr, N, sizeof(int), compare);
    int* zeroat = (int*)bsearch(&zero, arr, N, sizeof(int), compare);
    end_b = clock();

    if(zeroat)
        printf("\nexists");
    else
        printf("\ndoesn't exist");

    printf("\n%f", (double)(end_b - start_b) / CLOCKS_PER_SEC);

    start_c = clock();
    for(int j = 0; j < N; j++){
        if(arr[j] == 0)
            printf("\nexists");
            flag = 1;
    }
    end_c = clock();
    if(!flag)
        printf("\ndoesn't exist");

    printf("\n%f", (double)(end_c - start_c) / CLOCKS_PER_SEC);

    return 0;
}


int compare(const void* num1, const void* num2){
    int* b = (int*) num1;
    int* a = (int*) num2;
    if (*a > *b)
        return -1;
    else if(*a < *b)
        return 1;
    else
        return 0;
}