#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_LENGTH 50
#define LAST_SENTENCE "Dragon flew away!\n"

char *sentence();
char get_symbol();
int get_text_len(char ***input_text);
int check_entry(char *sentence);
void remove_symbol(char ***input_text, int *text_len);
void free_text(char ***input_text, int text_len);

int main() {
		
	char **text;
	int text_len = get_text_len(&text);
	int new_text_len = text_len;

	remove_symbol(&text, &new_text_len);

	for(int i=0; i<new_text_len; i++)
		printf("%s", text[i]);

	printf("Количество предложений до %d и количество предложений после %d\n", text_len - 1, new_text_len-1);

	free_text(&text, new_text_len);
	
	return 0;
}

char get_symbol(){
	char symbol;
	for(symbol = getchar(); symbol == ' ' || symbol == '\t' || symbol == '\n'; symbol = getchar()) {}

	return symbol;
}

char *sentence(){
	int sen_len = DEFAULT_LENGTH;
	char *temp = malloc(sen_len*sizeof(char));

	if(temp != NULL){
		char *sen = temp;
		char symbol = get_symbol();
		int i;

		for(i = 0; symbol != '.' && symbol != ';' && symbol != '?' && symbol != '!'; symbol = getchar()){
			sen[i++] = symbol;

			if(i == (sen_len - 2)){
				sen_len += DEFAULT_LENGTH;
				temp = realloc(sen, sen_len*sizeof(char));
				if(temp != NULL){
					sen = temp;
				} else {
					free(sen);
					return NULL;
				}
			}
		}
		sen[i++] = symbol;
		sen[i++] = '\n';
		sen[i] = '\0';

		return sen;
	}
	return NULL;
}

int get_text_len(char ***input_text){
	int text_len = DEFAULT_LENGTH;
	char **temp = malloc(text_len*sizeof(char**));

	if (temp != NULL){
		*input_text = temp;
		char *sen;
		int i = 0;

		for(sen = sentence(); strcmp(sen, LAST_SENTENCE) != 0; sen = sentence()){
			if(sen == NULL){
				free_text(input_text, i);
				return 0;
			}

			(*input_text)[i++] = sen;

			if(i == text_len){
				text_len += DEFAULT_LENGTH;
				temp = realloc(temp, text_len*sizeof(char**));
				if(temp != NULL){
					(*input_text) = temp;
				} else {
					free_text(input_text, i);
					return 0;
				}
			}
		}
		(*input_text)[i++] = sen;
		return i;
	}
	return 0;
}

int check_entry(char *sentence){
	for(int i=0; i<strlen(sentence); i++){
		if(sentence[i] == '7'){
			return 0;
		}
	}
	return 1;
}

void remove_symbol(char ***input_text, int *text_len){
	char **temp = malloc(*text_len*sizeof(char**));

	if(temp != NULL){
		char **output = temp;
		int n = 0;

		for(int i=0; i<*text_len; i++){
			if(check_entry((*input_text)[i])){
				output[n++] = (*input_text)[i];
			} else {
				free((*input_text)[i]);
			}
		}
		free(*input_text);
		*input_text = output;
		*text_len = n;
	}
}

void free_text(char ***input_text, int text_len){
	for(int i=0; i < text_len; i++){
		free((*input_text)[i]);
	}
	free(*input_text);
}


