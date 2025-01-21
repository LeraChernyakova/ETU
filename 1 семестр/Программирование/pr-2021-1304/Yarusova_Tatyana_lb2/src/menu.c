#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main(){
    int value;
    char c;
    scanf("%d", &value);
    int arr[100];
    int index;
    
    for(int i = 0; i < 100; i++){
    	scanf("%d%c", &arr[i],&c);
    	if (c == '\n'){
    		index = i;
    		break;
    		}
    	}
    switch (value){
        case 0: 
                printf("%d\n",abs_max(arr,index));
                break;
        case 1:
                printf("%d\n",abs_min(arr,index));
                break;
        case 2:
                printf("%d\n",diff(arr,index));
                break;
        case 3:
                printf("%d\n",sum(arr,index));
                break;
        default: 
                printf("Данные некорректны\n");
    }
    return 0;
 }
