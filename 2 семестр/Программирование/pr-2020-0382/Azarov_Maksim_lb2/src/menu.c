#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"



#include <stdio.h>

#define L 20




int getstr(int arr[]){
	
	char ch = 0;
	int i ;

	for (i = 0; ch != '\n'; i++){
	        scanf("%i",&arr[i]);
		ch = getchar();
        }	

	return i;

}





int main(){

	int flag,len,i,res,err;
	int arr[L];

	scanf("%d",&flag);

	len = getstr(arr);

	switch (flag){
		case 0: res = idx_frst_otr(arr,len);
		      	if (res == -1) printf("Данные некорректны\n");
			else printf("%i\n",res);
		        break;	

		case 1: res = idx_last_otr(arr,len);
			if (res == -1) printf("Данные некорректны\n");
		        else printf("%i\n",res);
			break;	

		case 2: res = mult_btwn_otr(arr,len,&err);
                        if (err == 1) printf("Данные некорректны\n");
                        else printf("%i\n",res);
		  	break;

		case 3: res = mult_bef_and_af_otr(arr,len,&err);
                        if (err == 1) printf("Данные некорректны\n");
                        else printf("%i\n",res);
			break;

		default: printf("Данные некорректны\n");	
	}	

	return 0;
}	

                                                                                                                                          






