#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EOT "Dragon flew away!"

int main(){	
	char **text;
	int total_count = 0, sentence = 0, count, state = 1, failed = 0;
	char c, temp;
	text = malloc(sizeof(char*));
	while (state){
		text = realloc(text, sizeof(char*) * (sentence + 2));
		text[sentence] = malloc(sizeof(char) * 2);
		count = 0;
		failed = 0;
		for (c = getchar(); c == '\t' || c == '\n' || c == ' '; c = getchar()) {}
		text[sentence][count] = c;
		text[sentence][count+1] = '\0';

		while ((c != '.') && (c != ';') && (c != '?') && (strcmp(text[sentence], EOT))){
			count++;
			c = getchar();
			text[sentence] = realloc(text[sentence], sizeof(char) * (count + 2));
			text[sentence][count] = c;
			text[sentence][count+1] = '\0';
			
		}
		if (c == '?') 
			failed = 1;

		if ((strcmp(text[sentence], EOT)) == 0)
			state = 0;

		if (failed){
			free(text[sentence]);
			sentence--;
		}
		sentence++;
		total_count++;
	}
	for(int i = 0; i < sentence; i++)
		printf("%s\n", text[i]);

	printf("Количество предложений до %d и количество предложений после %d\n", total_count-1, sentence-1);

    for(int i = 0; i < sentence; i++)
		free(text[i]);
	
	free(text);

	return 0;
}