#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#define LIMIT 100 //Limit of array.
#define ERROR "Данные некорректны\n" //Universal error message.

int main(){
    //Scan type of task and array of int.
    int type; scanf("%d\n", &type);
    int arr[LIMIT], count; char gap;
    for (count = 0, gap = ' '; gap != '\n'; count++)
        scanf("%d%c", &arr[count], &gap);
    
    //Print result of current task.
    int res_to_print; //To avoid calling funcs twice.
    switch (type){
        case 0:
            res_to_print = index_first_negative(arr, count);
            if (res_to_print < count)
                printf("%d\n", res_to_print);
            else printf(ERROR);
            break;
        case 1:
            res_to_print = index_last_negative(arr, count);
            if (res_to_print >= 0)
                printf("%d\n", res_to_print);
            else printf(ERROR);
            break;
        case 2:
            printf("%d\n", sum_between_negative(arr, count));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(arr, count));
            break;
        default:
            printf(ERROR);
    }
    
    return 0;
}
