#include <stdio.h>
#include <stdlib.h>
#define max_amount  100

int abs_max(int numbers[], int quantity){
	int maxnum = abs(numbers[0]);
	int maxindex = 0;
	for (int i = 1; i < quantity; i++){
		if( abs(numbers[i]) > abs(maxnum)){
			maxnum = abs(numbers[i]);
			maxindex = i;
		}
	}

	return maxindex;
}

int abs_min(int numbers[], int quantity){
	int minindex = 0;
	int minnum = abs(numbers[0]);
	for (int i = 1; i < quantity; i++){
		if( abs(numbers[i]) < minnum){
			minnum = abs(numbers[i]);
			minindex = i;
		}
	}

	return minindex;
}
    
int diff (int numbers[], int quantity){
	int diff = ( numbers[abs_max(numbers, quantity)] - numbers[abs_min(numbers, quantity)]);
	return diff;
}


int sum (int numbers[], int quantity){
	int sum = 0;
	for(int i = abs_max(numbers, quantity); i < quantity; i++){
		sum += numbers[i];	
	}
	return sum;
}

int main(){

	int arr[max_amount], arr_size = 0, choice;
	char sym = ' ';
	scanf("%d", &choice);
	while (arr_size < max_amount && sym == ' '){
		scanf("%d%c", &arr[arr_size++], &sym);
	}
	switch(choice){
	case 0:
		printf("%d\n", arr[abs_max(arr,arr_size)]);
		break;
	case 1:
		printf("%d\n", arr[abs_min(arr,arr_size)]);
		break;
	case 2:
		printf("%d\n",diff (arr,arr_size));
		break;
	case 3:
		printf("%d\n",sum (arr,arr_size));
		break;

	default:
		printf("Данные некорректны \n");
		
	}
	return 0;  
} 
