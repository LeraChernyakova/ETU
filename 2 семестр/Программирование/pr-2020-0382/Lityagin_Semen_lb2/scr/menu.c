#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main()
{
    int numbers[100];
    int index = 0;
    int value;

    scanf("%d", &value);

    while(getchar()!='\n'){
        scanf("%d", &numbers[index]);
        index++;
    }

    switch(value){
        case 0:
          printf("%d\n", abs_max(numbers, index));
          break;
        case 1:
          printf("%d\n", abs_min(numbers, index));
          break;
        case 2:
          printf("%d\n", diff(numbers, index));
          break;
        case 3:
          printf("%d\n", sum(numbers, index));
          break;
        default:
          printf("Данные некорректны\n");
          break;
    }

    return 0;
}
