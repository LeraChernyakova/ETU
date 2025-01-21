#include <stdio.h>
#include <stdlib.h>

int abs_max(int arr[100],int index){
    int max = abs(arr[0]);
    for(int i = 1; i <= index; i++){
        if (abs(arr[i]) > abs(max)){ 
                                max = arr[i];
        }
    }
    return max;
}

int abs_min(int arr[100], int index){
    int min = arr[0];
    for(int i = 1; i <= index; i++){
        if (abs(arr[i]) < abs(min)){
        	min = arr[i];
        }
    }
    return min;
}

int diff(int arr[100], int index){
    return (abs_max(arr,index) - abs_min(arr,index));
}

int sum(int arr[100],int index){
    int index_max;
    int max = abs_max(arr,index);
    for(int i = 0; i <= index;i++){
        if (max == arr[i]){
                                index_max = i;
                                break;
        }
    }
    int summa = 0;
    for (int j = index_max; j <= index; j++){
        summa += arr[j];
    }
    return summa;
}

int main(){
    int znachenie;
    char c;
    scanf("%d", &znachenie);
    int arr[100];
    int index;
    
    for(int i = 0; i < 100; i++){
    	scanf("%d%c", &arr[i],&c);
    	if (c == '\n'){
    		index = i;
    		break;
    		}
    	}
    switch (znachenie){
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
    
    			
