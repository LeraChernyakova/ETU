#include<stdio.h>
#include"abs_max.h"
#include"abs_min.h"
#include"diff.h"
#include"sum.h"

int main(void){
  int action, size=0;
  char s; 
  int arr[100];
  scanf("%d%c", &action, &s);
  while (size <= 100 && s == ' '){
      scanf("%d%c", &arr[size], &s);
      size++;
  }
  
  if (size == 0) 
    printf("Данные некорректны\n");
  else{
     switch (action){
      case 0: 
       printf("%d\n", abs_max(arr, size));
       break;
      case 1:
       printf("%d\n", abs_min(arr, size));
       break;
      case 2:
       printf("%d\n", diff(arr, size));
       break;
      case 3: 
       printf("%d\n", sum(arr, size));
       break;
      default:
       printf("Данные некорректны\n");
       break;
     }
  }
  return 0;
}
