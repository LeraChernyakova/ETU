#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int compare(const void * x1, const void * x2){
  return ( *(int*)x1 - *(int*)x2 );
}

int main(){
    int arr[10];
    int arr2[10];
    int buff;
    float uns1, uns2;
    _Bool flag;
    for(int i = 0; i < 10; i++){
        scanf("%d", &arr[i]);
        arr2[i] = arr[i];
    }
    clock_t timer1 = clock();
    for(int i = 10-1; i >=0; i--){
        flag = 1;
        for(int j = 0; j < i; j++){
            if(arr[j] > arr[j+1]){
                buff = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = buff;
                flag = 0;
            }
        }
        if(flag == 1){
            break;
        }
    }
    clock_t timer2 = clock();
    qsort(arr2, 10, sizeof(int), compare);
    clock_t timer3 = clock();
    for(int i = 0; i < 10; i++){
        printf("%d ", arr[i]);
    }
    uns1 = (float)(timer2 - timer1)/(CLOCKS_PER_SEC);
    uns2 = (float)(timer3 - timer2)/(CLOCKS_PER_SEC);
    printf("\n%f", uns1);
    printf("\n%f", uns2);
    return 0;
}
