#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int cmp(const void *a,const void *b){
	const char **aa=(const char **)a;
	const char **bb=(const char**)b;
 
	return strcmp(*aa,*bb);
 
}
int main(){

	char text[1000];
	char* str=malloc(30);
	char* arr_word[1000];
	
	fgets(text,1000,stdin);
	fgets(str,30,stdin);
	char* sep=" .\n";
	char* token=strtok(text,sep);
	
		
	int kol=0;
	while(token!=NULL){
		arr_word[kol]=token;
		kol++;
		token=strtok(NULL,sep);
		
	}
	
	
	qsort(arr_word,kol,sizeof(char*),cmp);
	
	
	
	char* ans = (char*) bsearch(&str,arr_word,kol,sizeof(char*),cmp);
	
	if(ans!=NULL) printf("exists");
	else printf("doesn't exist");
	
	
	free(str);
	return 0 ;
}
