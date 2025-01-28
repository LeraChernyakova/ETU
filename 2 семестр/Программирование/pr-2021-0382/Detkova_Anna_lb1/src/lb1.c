#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 1000

void getarray(int * mas, int sz){
    for (int i=0; i<sz; i++){
        scanf(" %d", &mas[i]);
    }
}

double bubblesort(int arr[], int sz){
    clock_t start = clock();
    for (int i=0; i<sz; i++){
        for (int j=0; j<sz-i-1; j++){
            if (arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    clock_t end = clock();
    double t = (double) (end - start)/CLOCKS_PER_SEC;
    return t;
}

int comparr(const void *a, const void *b){
    const int * aa = a;
    const int * bb = b;
    if (*aa > *bb) return 1;
    if (*aa == *bb) return 0;
    if (*aa < *bb) return -1;
}

int main(){
    
    int arr[SIZE];
    getarray(arr, SIZE);
    
    double timebuble = bubblesort(arr, SIZE);
    
    clock_t start = clock();
    qsort(arr, SIZE, sizeof(arr)/SIZE, *comparr);
    clock_t end = clock();
    double timeqsort = (double) (end - start)/CLOCKS_PER_SEC;
    
    for (int i=0; i<SIZE-1; i++){
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[SIZE-1]);
    printf("%f\n%f\n", timebuble, timeqsort);
    
    return 0;
}
