#include "func.h"



wchar_t ** delete_copy(struct Text parm)
{ 
	int n =parm.size;
	setlocale(LC_ALL,"");
	int q;
	int i;
	int j;
	int y;
	for(i =0;i < n;i++){						
		for ( y = 0; y < wcslen(parm.t[i]) ; y++) {
        		parm.t[i][y] = towlower(parm.t[i][y]);
        		 
						
	}
	}

	 i=0;
	while(i<n-1){
	j=i+1;
	while(j<n){
		q=0;
		if (wcslen(parm.t[i])== wcslen(parm.t[j])){
		for (int y = 0; y< wcslen(parm.t[i]) ; y++) {
        		if (parm.t[i][y] ==parm.t[j][y]){
				q=q+1;
				}
			}				
			if(q==wcslen(parm.t[i])){
				for (int y = 0; y< wcslen(parm.t[j]) ; y++){
				parm.t[j][y]=' ';
				}
			}	
		}	
	j++;
	}
	i++;
	} 	

return(parm.t);
}


void data(struct Text parm){
int n =parm.size;
setlocale(LC_ALL,"");
for(int i=0;i<n-1;i++){
	int slovo =1;
	int maxsl=0;
	int max=0;
	int q=0;
	int k=0;;		
	
	if(parm.t[i][0] != ' ' ){
	for (int y = 0; y < wcslen(parm.t[i]); y++) {
        		if (parm.t[i][y] == ' '){
        		slovo=slovo+1;
        		if(max<maxsl){
        		max=maxsl;
        		maxsl=0;
        		q=1;
        		}
        		maxsl =0;
        		}else{
        		if (parm.t[i][y] != ','){
        		maxsl=maxsl+1;
        		}
        		}        	
       } 	
        	int d=wcslen(parm.t[i]) + 1900 -1;              	
       	if(q==1 && max<maxsl){
       	max=maxsl-1;
       	}
       	if(q==0){
       	max=maxsl-1;
       	}
       	
        wprintf(L"%d%c%d%c%d \n",slovo,'-',max,'-',d);
    }  
}

}

void delete(struct Text parm){
int n =parm.size;
setlocale(LC_ALL,"");
for(int i=0;i<n-1;i++){
	int q=0;
	int maxsl=0;
	int max=0;
	if(parm.t[i][0] != ' ' ){
	for (int y = 0; y < wcslen(parm.t[i]); y++) {
        		if (parm.t[i][y] == ' '){        		
        		if(max<maxsl){
        		max=maxsl;
        		maxsl=0;
        		q=1;
        		}
        		maxsl =0;
        		}else{
        		if (parm.t[i][y] != ','){
        		maxsl=maxsl+1;
        		}
        		}        	
       } 	

if(q==1 && max<maxsl){
       	max=maxsl-1;
       	}
       	if(q==0){
       	max=maxsl-1;
       	}
 if(max>3){	
	wprintf(L"%ls\n",parm.t[i]);
	} 	
}
}


}

void reverse(struct Text parm){
 	int n =parm.size;
 	setlocale(LC_ALL,""); 	
 	for(int i=0;i<n-1;i++){
	if (parm.t[i][0] != ' ' ){	
	int len =wcslen(parm.t[i]);
	for (int y = len-1; y >= 0; y--) {        				
        		putwchar(parm.t[i][y]);    				        	
        	}       				 
	wprintf(L"  \n");
	} 
 	
 }

 }
 
void sort(struct Text parm){
	int q=0;
	int n =parm.size;
	setlocale(LC_ALL,"");
	int tmp;
	int arr[n];
	int arr2[n];
	for(int i=0;i<n;i++){	
	int maxsl=0;
	if(parm.t[i][0] != ' ' ){
	for (int y = 0; y < wcslen(parm.t[i]); y++) {
        		if (parm.t[i][y] == ' '|| parm.t[i][y]=='.' ){
        		break;        		
        		}else{
        		if (parm.t[i][y] != ','){
        		maxsl=maxsl+1;
        		}
        		}        	       	
	}
	arr[i]=maxsl;     
   	arr2[i]=maxsl;
   }

}
for(int i=0; i<n; i++){
            for(int j=i+1; j<n; j++){
                if (arr2[i] < arr2[j])
                {
                    tmp = arr2[j];
                    arr2[j] = arr2[i];
                    arr2[i] = tmp;
                }
	}
}
for(int i=0;i<n-1;i++){
	
	 for(int j=0; j<n-1; j++){
	 	if(arr2[i]==arr[j] && arr2[i]!=0){
	 	arr[j]=-1;
		wprintf(L"%ls \n",parm.t[j]);
		
	 	}
	 	
	 	}	 	 
	 }


}










