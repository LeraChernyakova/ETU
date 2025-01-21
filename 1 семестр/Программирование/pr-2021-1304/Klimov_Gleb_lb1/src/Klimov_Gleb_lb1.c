#include <stdio.h>
#include <stdlib.h>

int index_first_even(int arr[]){
	int index =0;
	int N=100;
	for(int i=0;i<N;i++){
		if (arr[i] % 2 == 0){
			index=i;
			break;
		}
	}
	return(index);
}

int index_last_odd(int arr[]){
	int N=100;
	int index =0;
	for(int i=0;i<N;i++){
		if (arr[i] % 2 != 0){
			index=i;
		}
	}
	return(index);
}

int sum_between_even_odd(int arr[]){
	int N=100;
	int sum =0;
	for(int i=index_first_even(arr);i<index_last_odd(arr);i++){
		sum +=abs(arr[i]);
	}
	return(sum);
}

int sum_before_even_and_after_odd( int arr[]){
	int N=100;
	int sum =0;
	for(int i=0;i<index_first_even(arr);i++){
		sum +=abs(arr[i]);
	}
	
	for(int i=index_last_odd(arr);i<N;i++){
		sum +=abs(arr[i]);
	}	
	
	return(sum);
}


int main(){
int n;
int N=100;
scanf("%d",&n);
int arr[N];
char ch;
int i=0;
for(i=0;i<N;i++){
 	arr[i]=0;
 }
 i=0;
 
 for(i=0;i<N;i++){
 	scanf("%d%c",&arr[i],&ch);
	if(ch =='\n'){
		break;
	}
 }

switch(n){
	case 0:
		printf("%d\n",index_first_even(arr));
		break;
	case 1:
		printf("%d\n",index_last_odd(arr));
		break;
	case 2:
		printf("%d\n",sum_between_even_odd(arr));
		break;
	case 3:
			printf("%d\n",sum_before_even_and_after_odd(arr));
		break;
	default:
	         printf("Данные некорректны");
}



return 0;


}

