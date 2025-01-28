#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
int main()
{
    char space =' ';
    int a[100];
    int inp, size = 0, ot;
    scanf("%d", &inp);
    while (size<100)
    {
        scanf("%d%c", &a[size++], &space);
        if(space !=' '){break;}
    }
    switch (inp)
    {
        case 0:
            ot = index_first_zero(a, size);
            printf("%d\n", ot);
            break;
        case 1:
            ot = index_last_zero(a, size);
            printf("%d\n", ot);
            break;
        case 2:
            ot = sum_between(a, size);
            printf("%d\n", ot);
            break;
        case 3:
            ot = sum_before_and_after(a, size);
            printf("%d\n", ot);
            break;

        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}