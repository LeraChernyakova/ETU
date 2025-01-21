#include "min.h"

int min(int array[], int index){
    int minimum = array[0], i = 0;
    for (i; i < index; i++)
        if (array[i] <= minimum)
        minimum = array[i];
    return minimum;
}
