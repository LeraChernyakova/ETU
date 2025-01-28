#include <stdio.h>

#define VOLUME 101      // нулевой элемент массива выделяется для "ключа" +
                        // 100 позиций для случая с максимально допустимым по условию кол-вом чисел
int max(int, int *);
int min(int, int *);    // прототипы функций
int diff(int, int *);
int sum(int, int *);

//---------------------------------------------------------------------------------\\

int main(){

    int Numbers[VOLUME];
    char Symb;
    int VLM;

    for (int i = 0; i < VOLUME; i++){               //считывание массива чисел
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

//---------------------------------------------------------------------------------\\

int max(int n, int  Arr[]){                         //f() поиск номера первого макс. элемента
    int maxi = 1;
    for(int i = 2; i <= n; i++){
        if (Arr[i] > Arr[maxi]) maxi = i;
    }
    return maxi;
}

int min(int n, int  Arr[]){                         //f() поиск номера первого мин. элемента
    int mini = 1;
    for(int i = 2; i <= n; i++){
        if (Arr[i] < Arr[mini]) mini = i;
    }
    return mini;
}

int diff(int n, int Arr[]){                         //f() разница между макс. и мин. элементами
    return (Arr[max(n, Arr)]-Arr[min(n, Arr)]);
}

int sum(int n, int Arr[]){                          //f() сумма всех встреченных элементов до первого мин. элемента в массиве
    int sumUN = 0;
    for (int i = 1; i < min(n, Arr); i++){
        sumUN += Arr[i];
    }
    return sumUN;
}
