#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "sum.h"
#include "diff.h"
#define max_amount 100
int main(){

    int arr[max_amount], arr_size = 0, choice;
    char sym = ' ';
    scanf("%d", &choice);
    while (arr_size < max_amount && sym == ' '){
        scanf("%d%c", &arr[arr_size++], &sym);
    }
    switch(choice){
        case 0:
            printf("%d\n", arr[abs_max(arr,arr_size)]);
            break;
        case 1:
            printf("%d\n", arr[abs_min(arr,arr_size)]);
            break;
        case 2:
            printf("%d\n",diff (arr,arr_size));
            break;
        case 3:
            printf("%d\n",sum (arr,arr_size));
            break;

        default:
            printf("Данные некорректны \n");

    }
    return 0;
}
