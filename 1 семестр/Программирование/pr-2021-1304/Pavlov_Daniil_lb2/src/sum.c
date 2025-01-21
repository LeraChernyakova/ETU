#include "sum.h"
#include "min.h"

int sum(int array[], int I){
      int minimum = min(array, I);
      int total = 0;
      for (int i = 1; i < I; i++){
          if (array[i] != minimum){
              total += array[i];
          }
          else{
              break;
          }
      }
      return total;
 }
