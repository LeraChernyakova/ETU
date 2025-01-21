#include "min.h"


int min(int array[], int I){        
     int minimum = array[1];
     for (int i = 1;i < I; i++){        
   	 if (minimum > array[i]){
             minimum = array[i];
         }
     }
     return minimum;
 }
