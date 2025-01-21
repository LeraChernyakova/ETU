#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main(){
	int k = 0, arr[100], operation;
	int mx, mn, su, dif;
	char value;
	scanf("%d", &operation);

	while(k < 100){
		scanf("%d%c", &arr[k], &value);
		k++;
		if (value == '\n'){
			break;
			}
		}
	mn = abs_min(arr, k);
	mx = abs_max(arr, k);
	su = sum(arr, k);
	dif = diff(arr, k);
	
	switch(operation){
		case 0:
		printf("%d\n", mx);
		break;
	    
		case 1:
		printf("%d\n", mn);
		break;
	    
		case 2:
		printf("%d\n", dif);
		break;
	    
		case 3:
		printf("%d\n", su);
		break;
	    
		default: puts("Данные некорректны\n");
	    }
	    return 0; 
	}

