#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXTEXTSIZE 10
#define MAXSENTENCESIZE 128


int main() {
	int text_len = 0;
	char last_sentence[] = "Dragon flew away!";
	char** p_for_text;
	char* p_for_sentence;
	int number_upper_symbols = 0;
	int max_text_len = MAXTEXTSIZE;
	int max_sentence_len = MAXSENTENCESIZE;
	char** text = malloc(sizeof(char*) * max_text_len);
	int i;
	for (i = 0; i < max_text_len; i++){
		text[i] = malloc(sizeof(char) * max_sentence_len);
	}
	char current_symbol;
	int sentence_index = 0;
	int char_index = 0;
	for (;;){
		current_symbol = getchar();
		if (current_symbol == '\t' || current_symbol == '\n'){
			continue;
		}
		if (char_index == 0 && current_symbol == ' '){
			continue;
		}
		if (current_symbol >= 'A' && current_symbol <= 'Z'){
			number_upper_symbols++;
			if (number_upper_symbols == 2){
				char_index = 0;
				number_upper_symbols = 0;
				text_len++;
				while (current_symbol != '.' && current_symbol != ';' && current_symbol != '?'){
					current_symbol = getchar();
				}
				continue;
			}
		}
		text[sentence_index][char_index++] = current_symbol;
		if (char_index == max_sentence_len){
			// add memory
			max_sentence_len *= 2;
			for (i = sentence_index; i < max_text_len; i++){
				p_for_sentence = realloc(text[i], sizeof(char) * max_sentence_len);
				if (p_for_sentence){
					text[i] = p_for_sentence;
				}
			}
		}
		if (current_symbol == '.' || current_symbol == ';' || current_symbol == '?' || current_symbol == '!'){
			// end of sentence
			text[sentence_index][char_index] = '\0';
			if (!strcmp(text[sentence_index], last_sentence)){
				sentence_index++;
				text_len++;
				break;
			}
			sentence_index++;
			text_len++;
			char_index = 0;
			number_upper_symbols = 0;
		}
		if (sentence_index == max_text_len){
			max_text_len *= 2;
			p_for_text = realloc(text, sizeof(char*) * max_text_len);
			if (p_for_text){
				text = p_for_text;
			}
			for (i = sentence_index; i < max_text_len; i++){
				text[i] = malloc(sizeof(char) * max_sentence_len);
			}
		}
	}
	for (i = sentence_index; i < max_text_len; i++){
		free(text[i]);
	}
	for (i = 0; i < sentence_index; i++){
		printf("%s\n", text[i]);
		free(text[i]);
	}
	free(text);
	printf("Количество предложений до %d и количество предложений после %d", text_len-1, sentence_index-1);
	return 0;
}