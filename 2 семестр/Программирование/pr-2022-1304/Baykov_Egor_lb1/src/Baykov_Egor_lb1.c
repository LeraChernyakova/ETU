#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void* a, const void* b){
    const int* f = (const int*)a;
    const int* s = (const int*)b;
    if(*f > *s){
        return 1;
    }
    if(*f < *s){
        return -1;
    }
    return 0;
}

int main(){
    int n = 1000;
    int arr[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, n, sizeof(int), compare);
    int key = 0;
    float start = clock();
    int* index = bsearch(&key, arr, n, sizeof(int), compare);
    float end = clock();
    if(index){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%f\n", end - start);
    int flag = 0;
    float new_start = clock();
    for(int i = 0; i < n; i++){
        if(key == arr[i]){
            flag = 1;
            break;
        }
    }
    float new_end = clock();
    if(flag){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%f\n", new_end - new_start);
    return 0;
}