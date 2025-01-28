#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main()
{
    int k = 0;
    scanf("%d", &k);
    int arr[100];
    int arr_size = 0;
    char sym = ' ';
    while (arr_size < 100 && sym == ' ')
    {
        scanf("%i%c", &arr[arr_size++], &sym);
    }
    switch (k)
    {
    case 0:
        printf("%d\n", index_first_even(arr, arr_size));
        break;
    case 1:
        printf("%d\n", index_last_odd(arr, arr_size));
        break;
    case 2:
        printf("%d\n", sum_between_even_odd(arr, arr_size));
        break;
    case 3:
        printf("%d\n", sum_before_even_and_after_odd(arr, arr_size));
        break;
    default: printf("Данные некорректны\n"); break;
    }
    return 0;
}