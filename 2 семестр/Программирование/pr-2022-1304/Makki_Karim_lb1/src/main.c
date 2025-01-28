#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void* a, const void* b){
    const int* f = (const int*)a;
    const int* s = (const int*)b;
    if(*f < *s)
        return -1;
    if(*f > *s)
        return 1;
    return 0;
}

int main(){
    int n = 1000;
    int key = 0;
    int cond = 0;
    int arr[n];
    
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    
    qsort(arr, n, sizeof(int), cmp);
    
    clock_t start = clock();
    int* tmp = bsearch(&key, arr, n, sizeof(int), cmp);
    clock_t end = clock();
    
    if(tmp)
        printf("exists\n");
    else
        printf("doesn't exist\n");
        
    printf("%ld\n", end - start);
    
    clock_t start_2 = clock();
    
    for(int i = 0; i < n; i++){
        if(key == arr[i]){
            cond = 1;
            break;
        }
    }
    
    clock_t end_2 = clock();
    
    if(cond)
        printf("exists\n");
    else
        printf("doesn't exist\n");
        
    printf("%ld\n", end_2 - start_2);
    return 0;
}
