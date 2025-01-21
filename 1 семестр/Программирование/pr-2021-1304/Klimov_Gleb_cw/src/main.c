#include "func.h"

int main(){	
	char c;
	int g; 
	int i;		
	setlocale(LC_ALL,"");
	wprintf(L"Ведите текст\n");
	struct Text tex =read();
	int n = tex.size;
	tex.t=delete_copy(tex);
	choice(); 
	c=getwchar();
	g=c -'0';
	  	
	switch (g) {
        	case 1:data(tex);                       
			break;
       	case 2:reverse(tex);                 
           		break;
        	case 3:sort(tex);                       
            		break;
        	case 4:delete(tex);                        
            		break;
        	case 5:
            		wprintf(L"Программа остановлена\n");             
    	}   
	
	for(i=0;i<n;i++){
		free(tex.t[i]);
	} 
	free(tex.t);
	
 return 0;  
}

