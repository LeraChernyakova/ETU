#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 200
#define M 200

int main(void) {

	char temp='q';
	char **sent;
	int size_sent=N;
	int size_word=M;
	char c;
	char* more;
	char** more_more;
	sent = malloc(size_sent * sizeof(char*));
		for(int i=0;i<size_sent;i++)
    sent[i] = malloc(size_word * sizeof(char));
    
 
    
	
	int len=0;
	int num_sent=0,num_el=0;
	int find_seven=0;
	char *end="Dragon flew away!";
	while(strcmp(end,sent[num_sent])!=0){
		
		temp=getchar();
		
		if(temp!='?' && temp!='.' && temp!=';'){
			
			if(size_word-num_el<=3){
			    size_word+=M;
			    more=realloc(sent[num_sent],size_word);
			    sent[num_sent]=more;
			}
			
			if(temp=='7')find_seven=1;
			
			sent[num_sent][num_el]=temp;
			num_el++;
			
		}else{
		    
		    	if(size_sent-num_sent<=3){
			        size_sent+=N;
			        more_more=realloc(sent,size_sent);
			        sent=more_more;
			}
		    
			sent[num_sent][num_el]=temp;
			num_el++;
			sent[num_sent][num_el]='\0';
			scanf("%c",&c);
			len++;
			if(find_seven==0){
			num_sent++;
			}else{
				for(int i =0;i<num_el;i++)
					sent[num_sent][i]=0;
			}
			num_el=0;
			find_seven=0;
			
		}
		
		
		
	}
	
	
	for(int i=0;i<num_sent;i++){
		printf("%s\n",sent[i]);
	}
	printf("Dragon flew away!\n");
	printf("Количество предложений до %d и количество предложений после %d",len,num_sent);
	
	
	for(int i=0;i<N;i++)
    	free(sent[i]);
	free(sent);
	
	
	return 0;
}
