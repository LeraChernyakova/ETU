#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{	
	char **a;
	char stop[]="Dragon flew away!";
	int m,n,counter,i,flag,flag2;
	flag=1;
	char c;
	a=malloc(sizeof(char*));
	n=0;
	m=0;
	while (flag){
		a=realloc(a,sizeof(char*)*(n+2));
		a[n]=malloc(sizeof(char)*2);
		scanf("%c",&c);
		a[n][0]=c;
		a[n][1]='\0';
		counter=0;
		flag2=0;
		while ((c!='.') && (c!=';') && (c!='?') && (strcmp(a[n],stop))){
			counter++;
			a[n]=realloc(a[n],sizeof(char)*(counter+2));
			scanf("%c",&c);
			if (c=='7'){
				flag2=1;
			}
			a[n][counter]=c;
			a[n][counter+1]='\0';
		}
		scanf("%c",&c);
		if ((strcmp(a[n],stop))==0){
			flag=0;
		}
		if (flag2){
			free(a[n]);
			n--;
		}
		n++;
		m++;
	}
	for(i=0;i<n;i++){
		printf("%s\n",a[i]);
	}
	for(i=0;i<n;i++){
		free(a[i]);
	}
	free(a);
	printf("Количество предложений до %d и количество предложений после %d\n",m-1,n-1);
}

