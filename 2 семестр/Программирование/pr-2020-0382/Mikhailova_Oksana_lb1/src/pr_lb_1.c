#include <stdio.h>
#include <stdlib.h>
#define N 100

int index_first_negative (int arr[N], int arr_size){
    for (int i=0; i<arr_size; i++){
        if (arr[i]<0){
            return i;
        }
    }
}

int index_last_negative (int arr[N], int arr_size){
    for (int i=(arr_size-1); i>=0; i--){
        if (arr[i]<0){
            return i;
        }
    }
}

int sum_between_negative (int arr[N], int arr_size){
    int sum = 0;
    int first, last, i;
    first = index_first_negative (arr, arr_size);
    last = index_last_negative (arr, arr_size);
    
    for (i=first; i<last; i++){
        sum=sum+abs(arr[i]);
    }
    
    printf ("%d", sum);
}

int sum_before_and_after_negative (int arr[N], int arr_size){
    int sum = 0;
    int first, last, i;
    first = index_first_negative (arr, arr_size);
    last = index_last_negative (arr, arr_size);
    
    for (i=0; i<first; i++){
        sum=sum+abs(arr[i]);
    }
    
    for (i=last; i<arr_size; i++){
        sum=sum+abs(arr[i]);
    }
    
    printf ("%d", sum);
    
}

int main(){
    int arr[N];
    int arr_size = 0;
    char sym = ' ';
    int res0, res1;
    
    int x;
    scanf ("%d", &x);
    
    while ((arr_size<N) && (sym == ' ')){
        scanf ("%d%c", &arr[arr_size++], &sym);
    }
    
    switch (x){
        case 0:
        res0=index_first_negative (arr, arr_size);
        printf ("%d", res0);
        break;
        case 1:
        res1=index_last_negative (arr, arr_size);
        printf ("%d", res1);
        break;
        case 2:
        sum_between_negative (arr, arr_size);
        break;
        case 3:
        sum_before_and_after_negative (arr, arr_size);
        break;
        default: 
        printf ("Данные некорректны");
    }
    return 0;
}
