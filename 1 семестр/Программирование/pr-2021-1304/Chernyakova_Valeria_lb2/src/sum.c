#include "sum.h"
#include "min.h"

int sum(int array[], int index){
    int summa = 0, i = 0;
    while (array[i] != min(array, index)){
        summa = summa + array[i];
        i++;
    }
    return summa;
}
