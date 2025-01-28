#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

#define VOLUME 101

int main(){

    int Numbers[VOLUME];
    char Symb;
    int VLM;

    int i;
    for (i = 0; i < VOLUME; i++){               //считывание массива чисел
        scanf("%d%c", &Numbers[i], &Symb);
        if (Symb == 10){//------------------проверка на "ENTER"
            VLM = i;//------------------количество полученных чисел
            break;}
    }

    switch (Numbers[0]){                                //обработка ключевого значения
    case 0: printf("%d\n", Numbers[max(VLM, Numbers)]);
        break;
    case 1: printf("%d\n", Numbers[min(VLM, Numbers)]);
        break;
    case 2: printf("%d\n", diff(VLM, Numbers));
        break;
    case 3: printf("%d\n", sum(VLM, Numbers));
        break;
    default: printf("Данные некорректны\n");
        break;
    }
    return 0;
}
