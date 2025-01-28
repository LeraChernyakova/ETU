#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 1000

int compare(const void* num1, const void* num2){
    const int* a = (const int*)num1;
    const int* b=  (const int*)num2;

    if(*a > *b){
        return 1;
    }
    else if(*a < *b){
        return -1;
    }
    return 0;
}


int main(){
    int arr[N];
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }

    time_t start, end;

    start = time(NULL);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N - i -1; j++){
            if(arr[j] > arr[j+1]){
                int buffer = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = buffer;
            }
        }
    }
    end = time(NULL);
    double bubble_time = difftime(end, start);

    start = time(NULL);
    qsort(arr,  N, sizeof(int),compare);
    end = time(NULL);
    double quick_time = difftime(end, start);

    for(int i = 0; i < N; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%lf", bubble_time);
    printf("\n%lf", quick_time);

    return 0;
}
