#include "index_first_negative.h"
int index_first_negative(int a[], int a_size){
    int fn;
    int i;
    for (i = 0; i < a_size; i++){
        if(a[i] < 0){
            fn = i;
            break;
    }
}
return fn;
}
