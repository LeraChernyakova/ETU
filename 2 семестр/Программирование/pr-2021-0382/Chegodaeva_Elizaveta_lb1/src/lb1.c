#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000
int cmp(const void* it1, const void* it2){
    int a = *(int *)it1;
    int b = *(int *)it2;
    return abs(b)-abs(a);
}
int main(){
    int t = 0;
    int arr[N];
    for (int i = 0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    clock_t time1 = clock();
    qsort(arr, N, sizeof(int), cmp);
    clock_t time2 = clock();
    t = ((int)time2-(int)time1)/CLOCKS_PER_SEC;
    for (int j = 0; j<N; j++){
        printf("%d", arr[j]);
        printf(" ");
    }
    printf("\n%d", t);
    return 0;
}

