#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int compare(const void* arg1, const void* arg2){
    if (abs(*(int*)arg2) > abs(*(int*)arg1)){
        return 1;
    }
    else if (abs(*(int*)arg2) == abs(*(int*)arg1)){
        return 0;
    }
    else if (abs(*(int*)arg2) < abs(*(int*)arg1)) {
        return -1;
    }
}

int main(){
    int arr[SIZE];
    int i;
    for (i=0; i<SIZE; i++){
        scanf("%d", &arr[i]);
    }
    int start, end;
    start = clock();
    qsort(&arr, SIZE, sizeof(int), compare);
    end = clock();
    for (i=0; i<SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%f", (double)(end - start)/CLOCKS_PER_SEC);
    return 0;
}
