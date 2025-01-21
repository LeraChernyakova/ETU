#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
#define N 101





int main()
{
    char c;
    int arr[N];
    int usr;
    int count = 0;
    int answ0, answ1, answ2, answ3;

    scanf("%d\n", &usr);
    while (count <= N)
    {
        scanf("%d%c", &arr[count], &c);
        count++;
        if (c == '\n')
        {
            break;
        }
        if (count > (N - 1))
        {
            printf("Данные некорректны");
            return 0;
        }
    }

    answ0 = abs_max(arr, count);
    answ1 = abs_min(arr, count);
    answ2 = diff(arr, count);
    answ3 = sum(arr, count, answ0);

    switch (usr)
    {
    case 0:
        printf("%d\n", answ0);
        break;
    case 1:
        printf("%d\n", answ1);
        break;
    case 2:
        printf("%d\n", answ2);
        break;
    case 3:
        printf("%d\n", answ3);
        break;
    default:
        puts("Данные некорректны");
    }

    return 0;
}





