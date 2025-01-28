#include "index_last_negative.h"
int index_last_negative(int a[], int a_size){
    int ln;
    int i;
    for(i = a_size - 1; i >= 0; i--){
        if(a[i] < 0){
        ln = i;
        break;
    }
}
return ln;
}

