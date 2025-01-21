#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

int main(){
	int command, array[100], len = 0;
	char sign;
	scanf("%d%c", &command, &sign);
	for (int i = 0; i < 100; i++){
		scanf("%d%c", &array[i], &sign);
		len += 1;
		if(sign == '\n'){
			break;
		}
	}
	switch(command){
		case 0:
			printf("\n%d", max(array, len));
			break;
		case 1:
			printf("\n%d", min(array, len));
			break;
		case 2:
			printf("\n%d", diff(array, len));
			break;
		case 3:
			printf("\n%d", sum(array, len));
			break;
		default:
			printf("\nДанные некорректны");
			break;
	}
	return 0;
}
