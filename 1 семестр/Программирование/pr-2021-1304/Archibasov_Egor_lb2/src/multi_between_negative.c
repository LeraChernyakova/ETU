#include " multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int array[], int length){
	int multi_between = 1;
	for(int i = index_first_negative(array, length); i < index_last_negative(array, length); i++){
		multi_between *=array[i];
	}
	return multi_between;
}
