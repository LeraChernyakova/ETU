#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main()
{
    int a, arr[100], arr_size, res;
    char sym = ' ';
    scanf("%d", &a);
    for (arr_size = 0; arr_size < 100 && sym == ' '; arr_size ++)
    {
         scanf("%d%c", &arr[arr_size], &sym);
    }
    switch (a)
    {case 0:
        res = index_first_zero(arr, arr_size);
        if (res != -1)
            printf("%d\n", res);
        else
            printf("Данные некорректны\n");
        break;
     case 1:
        res = index_last_zero(arr, arr_size);
        if (res != 100)
            printf("%d\n", res);
        else
            printf("Данные некорректны\n");
        break;
     case 2: 
        res = sum_between(arr, arr_size);
        if (res != -1)
            printf("%d\n", res);
        else
            printf("Данные некорректны\n");
        break;
     case 3:
        res = sum_before_and_after(arr, arr_size);
        if (res != -1)
            printf("%d\n", res);
        else
            printf("Данные некорректны\n");
        break;
     default:
         printf("Данные некорректны\n");
     }
    return 0;   
}
