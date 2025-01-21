#include <stdio.h>
#include <stdlib.h>
#define LIM 100

int index_first_negative(int* arr,int N){
        int first_i = 0;
        int i;
        for(i = 0; i<N; i++){
                if(arr[i] < 0){
                first_i = i;
                break;
                }
        }
        return(first_i);
}
int index_last_negative(int* arr,int N){
        int last_i = 0;
        int i;
        for(i = N-1;i>=0; i--){
                if(arr[i] < 0){
                last_i = i;
                break;
                }
        }
        return(last_i);
}
int sum_between_negative(int* arr,int N){
        int sum = 0;
        int i;
        for(i = index_first_negative(arr,N); i < index_last_negative(arr,N); i++){
                sum += abs(arr[i]);
        }
        return(sum);
}
int sum_before_and_after_negative(int* arr,int N){
        int sum = 0;
        int i;
        for(i = 0;i <index_first_negative(arr,N);i++){
                sum += abs(arr[i]);
        }
        for(i = index_last_negative(arr,N);i<N;i++){
                sum += abs(arr[i]);
        }
        return(sum);
}
int print_arr(int* arr){
    int i; char ch;
    for (i = 0, ch = ' '; ch != '\n'; i++)
        scanf("%d%c", &arr[i], &ch);
    return i;
}
int main(){
        int comand;
        scanf("%d",&comand);
        int arr[LIM];
        int N = print_arr(arr);
        switch(comand){
                case 0:
                        if(index_first_negative(arr, N) < N){
                        printf("%d\n", index_first_negative(arr, N));
                        }
                        else{
                        printf("Данные некорректны\n");
                        }
                        break;
                case 1:
                        if(index_last_negative(arr,N) >= 0){
                        printf("%d\n",index_last_negative(arr,N));
                        }
                        else{
                        printf("Данные некорректны\n");
                        }
                        break;
                case 2:
                        printf("%d\n", sum_between_negative(arr,N));
                        break;
                case 3:
                        printf("%d\n", sum_before_and_after_negative(arr,N));
                        break;
                default:
                        printf("Данные некорректны\n");
        }
        return 0;
}
