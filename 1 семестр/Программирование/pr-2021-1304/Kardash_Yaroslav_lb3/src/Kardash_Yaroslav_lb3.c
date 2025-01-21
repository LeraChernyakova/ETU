#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define del_comb "555"
#define break_sent "Dragon flew away!\n"
#define stand 100
char skip_tab(){ //удаление табов в начале предложения (пропуск)
	char character;
	for (character = getchar(); character == ' ' || character == '\t' 		|| character == '\n'; character = getchar()) {}
	return character;
}
void free_text(char*** text,int len){ //удаление выделенной динамической памяти 
for (int i=0;i<len;i++){
	free((*text)[i]);
}
free(*text);

}
char* get_sent(){
	int s_size = stand;
	char *buf = malloc(s_size*sizeof(char)); 
	if (buf) {
		char *sent = buf;	
		char character = skip_tab();
		int i;
		for (i = 0; character != '.' && character != ';' && character != '?' && character != '!'; character = getchar()) 
		{	
			sent[i++] = character;

			if (i == s_size-2) 
			{
				s_size += stand;
				buf = realloc(sent, s_size*sizeof(char));
				if (buf) 
				{
					sent = buf;
				} else 
				{
					free(sent);
					return NULL;
				}
			}
		}

		sent[i++] = character;
		sent[i++] = '\n';
		sent[i] = '\0';
		return sent;
	}
	return NULL;	

}

int get_text(char ***text) {
	int t_size =stand;
	char** buf = malloc(t_size*sizeof(char**));
	if (buf) {
		*text = buf;
		char *sent;
		int i = -1;
		for (sent = get_sent(); strcmp(sent, break_sent) != 0; sent 			= get_sent()) 
		{	
			
			if (sent == NULL) 
			{
				free_text(text, i);
				return 0;
			}

			(*text)[++i] = sent;
			if (i == t_size) {
				t_size += stand;
				buf = realloc(buf, t_size*sizeof(char**));
				if (buf) 
				{
					(*text) = buf;
				} else 
				{
					free_text(text, i);
					return 0;
				}
			}
		}

		(*text)[++i] = sent;
		i+=1;
		return i;
	}
	return 0;
}

int del_comb_in(char c){
	if ((c < '0' || c > '9') && (c < 'A' || c > 'Z') && (c < 'a' || c > 		'z')) {
	return 1;}
	else{
	return 0;}

}
int check_del(char* sent){
	int f;
	for(int i=0; i<strlen(sent)-strlen(del_comb); i++){
		f=1;
		for (int j=0;j<strlen(del_comb);j++){
			if (sent[i+j]!=del_comb[j]){
				f=0;
				break;
			
			}
		
		}
		if  (f&&((i==0||				del_comb_in(sent[i-1]))&&(del_comb_in(sent[i+strlen(del_comb)])))){
		return 1;}	
	}
	return 0;
	
	
}

void del(char ***text, int* len){
	int t_len=*len;
	int i=0;
	while(i<t_len){
		if (check_del((*text)[i])){
			free((*text)[i]);
			memmove(&(*text)[i],&(*text)[i+1],(t_len-	i+1)*sizeof(char*));
			t_len--;
		}
		else{
			i++;
		}

	}
	*len = t_len;
}


int main(){
char** text;
int len= get_text(&text);
int len_aft = len;
del(&text, &len_aft);
for (int i=0;i<len_aft;i++){
	printf("%s",text[i]);
}
printf("Количество предложений до %d и количество предложений после %d", len-1,len_aft-1);
free_text(&text,len_aft);
return 0;
}
