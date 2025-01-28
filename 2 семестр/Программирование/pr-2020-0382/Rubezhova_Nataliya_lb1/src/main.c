#include <stdio.h>
#include <stdlib.h>
int index_first_negative(int arr[], int n){ // n - размер массива
    for(int i=0;i<n;i++){
        if(arr[i]<0){
            return i;
        }
    }
}
int index_last_negative(int arr[], int n){
    int i_last=-1;
    for(int i=0;i<n;i++){
       if(arr[i]<0)i_last=i;
    }
    return i_last;
}
int multi_between_negative(int arr[],int a,int b){ //a - индекс первого отриц.элемента массива; b - индекс последнего отриц.элемента массива;
    int p=1;
    for(int i=a;i<b;i++)p*=arr[i];
    return p;
}

int multi_before_and_after_negative(int arr[],int n,int a,int b){
    int p=1;
    for(int i=0;i<a;i++)p*=arr[i];
    for(int i=b;i<n;i++)p*=arr[i];
    return p;
}
int main()
{
    int inp=0;
    int arr[20]={0};
    int arr_size=0;
    char sym = ' ';

    scanf("%d",&inp);

    while(arr_size<20&&sym==' '){
        scanf("%d%c",&arr[arr_size++],&sym);
    }

    switch(inp){
        case 0: {
            printf("%d\n", index_first_negative(arr,arr_size));
            break;
        }
        case 1: {
            printf("%d\n", index_last_negative(arr,arr_size));
            break;
        }
        case 2: {
            int a=index_first_negative(arr,arr_size);
            int b=index_last_negative(arr,arr_size);
            printf("%d\n", multi_between_negative(arr,a,b));
            break;
        }
        case 3: {
            int a=index_first_negative(arr,arr_size);
            int b=index_last_negative(arr,arr_size);
            printf("%d\n", multi_before_and_after_negative(arr,arr_size,a,b));
            break;
        }
        default: {
            printf("%s\n","Данные некорректны");
            break;
        }
    }
}
