#include "sum.h"
#include "min.h"

//f() сумма всех встреченных элементов до первого мин. элемента в массиве

int sum(int n, int Arr[]){
    int sumUN = 0;
    int i;
    for (i = 1; i < min(n, Arr); i++){
        sumUN += Arr[i];
    }
    return sumUN;
}
