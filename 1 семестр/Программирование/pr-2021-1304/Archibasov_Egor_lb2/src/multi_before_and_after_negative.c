#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int array[], int length){
	int multi_before_and_after= 1;
	for(int i = 0; i < index_first_negative(array, length); i++){
		multi_before_and_after*=array[i];
	};
	for(int i = index_last_negative(array, length); i < length ; i++){
		multi_before_and_after*=array[i];
	};
	return multi_before_and_after;
}
