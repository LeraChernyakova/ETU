#include <stdio.h>
#include <stdlib.h>
#include "index_last_zero.h"

int index_last_zero(int fnumb[], int length){
    int i, thelast=0;
    for (i=0; i<length; i++){
        if (fnumb[i]==0) thelast = i;
    }
    return thelast;
}
