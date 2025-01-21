#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{	
	char **text;
	char text_end[]="Dragon flew away!";
	int m,n,counter,i,d,q;
	d=1;
	char c;
	text=malloc(sizeof(char*));
	n=0;
	m=0;
	
	while (d){
		
		text=realloc(text,sizeof(char*)*(n+2));
		text[n]=malloc(sizeof(char)*2);
		scanf("%c",&c);
		text[n][0]=c;
		text[n][1]='\0';
		counter=0;
		q=0;
		while ((c!='.') && (c!=';') && (c!='?') && (strcmp(text[n],text_end))){
			
			counter= counter +1;
			text[n]=realloc(text[n],sizeof(char)*(counter+2));
			scanf("%c",&c);
			if (c=='?'){
				q=1;
			}
			
			text[n][counter]=c;
			text[n][counter+1]='\0';
		}
		
		scanf("%c",&c);
		if ((strcmp(text[n],text_end))==0){
			d=0;
		}
		
		if (q==1){
			free(text[n]);
			n=n-1;
		}
		
		n=n+1;
		m=m+1;
	}
	
	for(i=0;i<n;i++){
		printf("%s\n",text[i]);
	}
	
	for(i=0;i<n;i++){
		free(text[i]);
	}
	
	free(text);
	printf("Количество предложений до %d и количество предложений после %d\n",m-1,n-1);

    return 0;
}
