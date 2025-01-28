#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"

int index_first_zero(int fnumb[], int length){
    int i;
    for (i=0; i<length && fnumb[i]!=0; i++){
    }
    return i;
}
