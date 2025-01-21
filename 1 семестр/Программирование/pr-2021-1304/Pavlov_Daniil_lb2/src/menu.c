#include <stdio.h>
#include "min.h"
#include "max.h"
#include "diff.h"
#include "sum.h"


int main(){
     int arr[MAX_BUFFER];
     char c;
     int size = 0;
     for(int i = 0; i < MAX_BUFFER; i++){
         scanf("%d%c", &arr[i], &c);
         size++;
         if (c == '\n'){
             break;
         }

     }



     switch (arr[0]) {
         case 0:
             printf("\n%d", max(arr, size));
             break;
         case 1:
             printf("\n%d", min(arr, size));
             break;
         case 2:
             printf("\n%d", diff(arr, size));
             break;
         case 3:
             printf("\n%d", sum(arr, size));
             break;
         default:
             printf("\nДанные некорректны");
     }
     return 0;
 }
