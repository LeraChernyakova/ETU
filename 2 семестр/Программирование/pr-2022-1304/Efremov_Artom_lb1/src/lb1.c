#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void bsort(int* arr, int N){
    for (int i = 0; i < N-1; i++){
        for (int j = 0; j < N - i - 1; j++){
            int p = arr[j];
            if (arr[j+1] < arr[j]){
                arr[j] = arr[j+1];
                arr[j+1] = p;
            }
        }
    }
}

int cmp(const void* a, const void* b){
    int f = *((int*)a);
    int s = *((int*)b);
    return f - s;
}

int main(){
    int N = 1000;
    clock_t bstart, qstart, bend, qend;
    int arr[N], arr1[N];
    for (int i = 0; i < N; i++){
			scanf("%i", &arr[i]);
			arr1[i] = arr[i];
		}
    bstart = clock();
    bsort(arr, N);
    bend = clock();
    float total_btime = (float)(bend-bstart)/CLOCKS_PER_SEC;
    
    qstart = clock();
    qsort(arr1, N, sizeof(int), cmp);
    qend = clock();
    float total_qtime = (float)(qend-qstart)/CLOCKS_PER_SEC;
    
    for (int i = 0; i < N; i++)
        printf("%i ", arr[i]);
    printf("\n%f\n", total_btime);
    printf("%f\n", total_qtime);
}
