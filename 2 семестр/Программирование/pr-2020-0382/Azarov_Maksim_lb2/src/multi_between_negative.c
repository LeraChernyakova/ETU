#include "index_first_negative.h"
#include "index_last_negative.h" 


int mult_btwn_otr(int arr[],int len,int *err){
	int from,to,i,res;
	res = 1;
	*err = 0;
	from = idx_frst_otr(arr,len);
	to = idx_last_otr(arr,len);

	if ((to == -1)||(from == -1)){
	       	*err = 1;
		return 0;
	}	
        else { 
		for (i = from; i < to; ++i)
			res = res * arr[i];
		return res;
	}
}
