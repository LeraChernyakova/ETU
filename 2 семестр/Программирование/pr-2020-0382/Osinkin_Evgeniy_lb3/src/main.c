#include <stdio.h>
#include <stdlib.h>

int scan_text(char*** text, int** size) {
	char chr = '\0';
	int index = 0;
	int* len = *size;
	len = (int*)malloc(1 * sizeof(int));
	char** sent = *text;
	sent = (char**)malloc((index + 1) * sizeof(char*));
	while (chr != '!') {
		scanf("%c", &chr);
		if ((chr != ' ') && (chr != '\t') && (chr != '\n')) {
			int number = 0;
			int sent_size = 1;
			sent[index] = (char*)malloc(sent_size * sizeof(char));
			*(sent[index] + number) = chr;
			while ((chr != '.') && (chr != ';') && (chr != '?') && (chr != '!')) {
				scanf("%c", &chr);
				if ((chr != '\t') && (chr != '\n')) {
					sent_size++;
					number++;
					sent[index] = (char*)realloc(sent[index], sent_size * sizeof(char));
					*(sent[index] + number) = chr;
				}
			}
			sent[index] = (char*)realloc(sent[index], (sent_size + 1) * sizeof(char));
			*(sent[index] + number + 1) = '\0';
			*(len + index) = sent_size;
			index = index + 1;
			sent = (char**)realloc(sent, (index + 1) * sizeof(char*));
			len = (int*)realloc(len, (index + 1) * sizeof(int));
		}
		*size = len;
		*text = sent;
	}
	return index;
}

int delete_wrong_sentences(char** text, int* size, int index) {
	int count = index;
	for (int i = 0; i < index; i++) {
		for (int j = 0; j<size[i]; j++) {
			if (text[i][j] == '7') {
				count--;
				text[i][0] = '\0';
				break;
			}
		}
	}
	return count;
}

int main() {
	int* size;
	char** text;
	int index = scan_text(&text, &size);
	int count = delete_wrong_sentences(text, size, index);
	for (int i = 0; i < index; i++) {
		if (text[i][0] != '\0') {
			printf("%s\n", text[i]);
		}
	}
	printf("Количество предложений до %d и количество предложений после %d\n", index - 1, count - 1);
	for (int j = 0; j < index; j++) {
		free(text[j]);
	}
	free(text);
	return 0;
}
