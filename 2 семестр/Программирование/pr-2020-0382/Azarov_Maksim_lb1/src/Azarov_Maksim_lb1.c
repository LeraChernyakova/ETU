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



int idx_frst_otr(int arr[],int len){
	int i, bol = 0,res;

	for (i = 0; (i < len)&&(bol == 0);++i)
		if (arr[i] < 0){
			res = i;
			bol = 1; 
		}	
	if (bol == 1) return res;
	else return -1;
        

}	


int idx_last_otr(int arr[],int len){
	int i,bol = 0,res;

	for (i = 0; i < len ;++i)
	        if (arr[i] < 0){
	                res = i;
                        bol = 1;
                }
        if (bol == 1) return res;
       	else return -1;
 
	

}	


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


int mult_bef_and_af_otr(int arr[],int len,int *err){
	int from,to,i,res;
	res = 1;
	*err = 0;
	to = idx_frst_otr(arr,len);
        from = idx_last_otr(arr,len); 

	if ((to == -1)||(from == -1)){
	       	*err = 1;
		return 0;
	}
	else{	
        	for (i = 0; i < to; ++i)
		        res = res * arr[i];
		for (i = from; i < len; ++i)
			res = res * arr[i];
		return res;
	}
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

                                                                                                                                          






