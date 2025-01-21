#include<stdio.h>
#include<stdlib.h>
#include "diff.h"
#include "sum.h"
#define N 100
int main()
{
    char c;
    int array[N];
    int choice;
    int size = 0;
    int max;
    scanf("%d\n", &choice);
    while (size <= N)
    {
        scanf("%d%c", &array[size], &c);
        size++;
        if (c == '\n')
        {
            break;
        }
        if (size < 1)
        {
            printf("Данные некорректны");
            return 0;
        }
    }
    switch (choice)
    {
    case 0:
        printf("%d\n", abs_max(array, size));
        break;
        
    case 1:
        printf("%d\n", abs_min(array, size));
        break;
    case 2:
        printf("%d\n", diff(array, size));
        break;
    case 3:
        max = abs_max(array, size);
        printf("%d\n", sum(array, size, max));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
 
    return 0;
}
 
