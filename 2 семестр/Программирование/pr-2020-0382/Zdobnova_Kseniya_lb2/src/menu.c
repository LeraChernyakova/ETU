#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main()
{
    int array[101];
    char character;
    int command, array_size = 0;
    scanf("%d%c", &command, &character);
    while (array_size <= 100 && character == ' '){
        scanf("%d%c", &array[array_size], &character);
        array_size++;
    }
    if (array_size == 0)
        printf("Данные некорректны\n");
    else {
        switch(command){
        case 0:
            printf("%d\n", array[abs_max(array_size, array)]);
            break;
        case 1:
            printf("%d\n", array[abs_min(array_size, array)]);
            break;
        case 2:
            printf("%d\n",diff(array_size, array));
            break;
        case 3:
            printf("%d\n", sum(array_size, array));
            break;
        default:
            printf("Данные некорректны\n");
            break;
        }
    }
    return 0;
}
