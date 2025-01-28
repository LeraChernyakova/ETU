#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
int main(){
    int n = -1, list[100]; // n - значение для функции, list - список для вводимых символов
    int listsize = 0; // насколько массив заполнен

    char sym = ' ';
    while(listsize<100 && sym == ' '){ //Ввод
        if (n == -1) scanf("%d%c", &n, &sym);
        else scanf("%d%c", &list[listsize++], &sym);
    }

    switch (n)
    {
    case 0:
        printf("%d\n", index_first_even(list, listsize));
        break;
    case 1:
        printf("%d\n", index_last_odd(list, listsize));
        break;
    case 2:
        printf("%d\n", sum_between_even_odd(list, listsize));
        break;
    case 3:
        printf("%d\n", sum_before_even_and_after_odd(list, listsize));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
    return 0;
}