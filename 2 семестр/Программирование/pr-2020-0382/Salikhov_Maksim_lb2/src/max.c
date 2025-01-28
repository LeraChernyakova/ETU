#include "max.h"

//f() поиск номера первого макс. элемента

int max(int n, int  Arr[]){
    int maxi = 1;
    int i;
    for(i = 2; i <= n; i++){
        if (Arr[i] > Arr[maxi]) maxi = i;
    }
    return maxi;
}
