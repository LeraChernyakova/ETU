#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
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
            printf("%d\n", multi_between_negative(arr,arr_size));
            break;
        }
        case 3: {
            printf("%d\n", multi_before_and_after_negative(arr,arr_size));
            break;
        }
        default: {
            printf("%s\n","Данные некорректны");
            break;
        }
    }
}
