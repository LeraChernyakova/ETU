#include "max.h"

int max(int array[], int index){
    int maximum = array[0], i = 0;
    for (i; i < index; i++)
        if (array[i] > maximum)
        maximum = array[i];
    return maximum;
}
