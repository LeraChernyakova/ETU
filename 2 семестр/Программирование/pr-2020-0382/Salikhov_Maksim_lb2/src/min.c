#include "min.h"

//f() поиск номера первого мин. элемента

int min(int n, int  Arr[]){
    int mini = 1;
    int i;
    for(i = 2; i <= n; i++){
        if (Arr[i] < Arr[mini]) mini = i;
    }
    return mini;
}
