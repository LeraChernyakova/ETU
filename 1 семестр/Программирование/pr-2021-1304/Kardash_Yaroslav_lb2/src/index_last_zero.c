#include "index_last_zero.h"
int index_last_zero(int arr[],int n){
	int index=0;
	for (int i=n-1;i>=0;i--){
		if (arr[i]==0){
		index=i;
		break;}
	}
	return index;
}
