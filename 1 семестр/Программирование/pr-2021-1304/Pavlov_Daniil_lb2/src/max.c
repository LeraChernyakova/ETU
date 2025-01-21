#include "max.h"

int max(int array[], int I){
     int maximum = 0;
     for (int i = 1;i < I; i++){
         if (maximum < array[i]){
             maximum = array[i];
         }
     }
     return maximum;
 }
