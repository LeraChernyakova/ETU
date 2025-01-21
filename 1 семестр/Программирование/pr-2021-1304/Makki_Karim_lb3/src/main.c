#define N 50
#define M 10
#define G 10
#define end "Dragon flew away!"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int punc(char *text,int i){
	if (text[i]!='.' && text[i]!='?'  && text[i]!=';' && text[i]!='!')
		return 1;
	else
		return 0;
}

int find(char *text,int i,int len){
	int j;
	for (j=i;j<len;j++)
		if (!(punc(text,j)))
			return j-1;
    	return j;
}

char *read(int *res){	
	int i=0,len=N;
	int n=strlen(end);
	char *text=malloc(sizeof(char)*N);
	char c;
	while (i<n || strncmp(end,text+i-n,n-1)){
		scanf("%c",&c);
        if (c!='\n'){
        	text[i]=c;
            if (!(punc(text,i)))
            	(*res)++;
            i++;
		    if (i>=len-2){
		       	text=realloc(text,sizeof(char)*(len+N));
			    len+=N;
			}
	    }
	}

    text[i]='\0';
	return text;
}

void free_all(char **s,int len){
	for (int i=0;i<len;i++)
		free(s[i]);
	free(s);
}

void printlist(char **s,int len){
	for (int i=0;i<len;i++)
        	printf("%s\n",s[i]);
	}

int main(){
	char *text=NULL;
	char **sentense=malloc(sizeof(char *)*G);
	int i=0,k=0,j=0,b=0;
	int res=0;
	text=read(&res);
	sentense[0]=malloc(sizeof(char)*M);
	int text_len=strlen(text);
	while (i<text_len){	
		if (punc(text,i)){
			if (text[i]=='5' && text[i+1]=='5'  && text[i+2]=='5' && (!punc(text,i+3) || text[i+3]==' ') && (k==0 || text[i-1]==' ')){
				i=find(text,i,text_len);
				free(sentense[j]);
				b=1;
			}
			else
				sentense[j][k]=text[i];
			k++;
			if (k>=M)
		            sentense[j]=realloc(sentense[j],sizeof(char)*(k+2));
	        i++;
		}else{
			if (!b){
				sentense[j][k]=text[i];
				sentense[j][k+1]='\0';
				j++;
			}else
				b=0;
			if (j>=G)
				sentense=realloc(sentense,sizeof(char*)*(j+1));
			sentense[j]=malloc(sizeof(char)*M);
			k=0;
			i++;
			while (text[i]=='\t' ||  text[i]==' ')
				i++;
		}
	}
printlist(sentense,j);
printf("Количество предложений до %d и количество предложений после %d\n",res-1,j-1);
free(text);
free_all(sentense,j);
}
