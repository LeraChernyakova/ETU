#include  <stdio.h>
#include ”index_first_negative.h”
#include “index_last_neganive.h”
#include “sum_between_negative.h”
#include “sum_befor_and_after_negative.h”
#define LIM 100

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

