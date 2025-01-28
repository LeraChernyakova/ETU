#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void* a, const void* b){
        const int* x = (const int*)a;
        const int* y = (const int*)b;
        if(*x > *y){
                return 1;
        }
        if(*x < *y){
                return -1;
        }
                
        return 0;
}
int main(){
    int N = 1000;
    int arr[N];
    for(int i = 0;i<N;i++){
        scanf("%d",&arr[i]);
    }
    qsort(arr,N,sizeof(int),cmp);
    int a = 0;
    float s = clock();
    int* index = bsearch(&a, arr, N, sizeof(int), cmp);
    float e = clock();
    if(index){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%f\n", e - s);
    int f = 0;
    float new_s = clock();
    for(int i = 0; i < N; i++){
        if(a == arr[i]){
            f = 1;
            break;
        }
    }
    float new_e = clock();
    if(f){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%f\n", new_e - new_s);
    return 0;

}
