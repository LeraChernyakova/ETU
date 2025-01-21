#include<stdio.h>
#include<stdlib.h>
#include "max_num.h"
#include "min_num.h"
#include "diff_num.h"
#include "sum_num.h"


int arr_inp(int arr[]){
	char sep;
	int n = 0;
	for (int i = 0; i < 100; i++){
		scanf("%d%c", &arr[i], &sep);
		n++;
			if(sep == '\n'){
				break;
			}
	}
	return n;
}

int main(){
	int arr[100];
	int n = arr_inp(arr);
	switch(arr[0]) {
            case 0:
              printf("%d\n", max_num(arr, n));
              break;
            case 1:
              printf("%d\n", min_num(arr, n));
              break;
            case 2:
              printf("%d\n", diff_num(arr, n)); 
              break;
            case 3:
              printf("%d\n", sum_num(arr, n));
              break;
            default:
              printf("Данные некорректны\n");
        }
        return 0;	
}
