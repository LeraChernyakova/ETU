#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//___SCAN
void scan_text(char*** text, int* size) {
	printf("Введите текст и закончите ввод, нажав клавишу Enter:\n");
	char chr = '\0';
	int size_sent = 1;
	int count_sents = 1;
	char** sents = (char**)malloc(count_sents * sizeof(char*));
	while (chr != '\n') {
		scanf("%c", &chr);
		if  ((chr != '\n') && (chr != ' ') && (chr != ',')) {
			char* sent = (char*)malloc(size_sent * sizeof(char));
			sent[size_sent - 1] = chr;
			while (chr != '.') {
				scanf("%c", &chr);
				if (!(((chr == ' ') || (chr == ',')) && ((sent[size_sent - 1] == ' ') || (sent[size_sent - 1] == ',')))) {
					if ((chr == '.') && ((sent[size_sent - 1] == ' ') || (sent[size_sent - 1] == ','))) {
						printf("%c\n", sent[size_sent - 1]);
						sent[size_sent - 1] = '.';
						break;
					}
					size_sent++;
					sent = (char*)realloc(sent, size_sent * sizeof(char));
					sent[size_sent - 1] = chr;
				}
			}
			sent = (char*)realloc(sent, (size_sent + 1) * sizeof(char));
			sent[size_sent] = '\0';
			size_sent = 1;
			if (count_sents != 1) 
				sents = (char**)realloc(sents, (count_sents) * sizeof(char*));
			sents[count_sents - 1] = sent;
			count_sents++;
		}
	}
	count_sents--;
	*size = count_sents;
	*text = sents;
}

//___DELETE_SIMILAR
bool is_similar_sents(char* strA, char* strB) {
	int i = 0;
	while ((strA[i] != '.') && (strB[i] != '.')) {
		if ((char)tolower(strA[i]) != (char)tolower(strB[i])) {
			return 0;
		}
		i++;
	}
	if (strA[i] != strB[i]) {
		return 0;
	}
	else {
		return 1;
	}
}

void delete_similar_sents(char*** text, int* size) {
	char** tmp_text = *text;
	char** new_text = *text;
	int new_size = 0;
	for (int i = 0; i < *size - 1; i++) {
		for (int j = i + 1; j < *size; j++) {
			char* strA = tmp_text[i];
			char* strB = tmp_text[j];
			if (is_similar_sents(strA, strB)) {
				tmp_text[j] = " \0";
			}
		}
	}
	for (int i = 0; i < *size; i++) {
		if (tmp_text[i] != " \0") {
			new_text[new_size] = tmp_text[i];
			new_size++;
		}
	}
	new_text = (char**)realloc(new_text, new_size * sizeof(char*));
	*text = new_text;
	*size = new_size;
}


//___1
int word_count(char* sent) {
	int i = 0;
	int count = 0;
	while (sent[i] != '.') {
		if ((sent[i] == ' ') || (sent[i] == ',')) {
			count++;
		}
		i++;
	}
	count++;
	return count;
}

void delete_even_sents(char*** text, int* size) {
	char** tmp_text = *text;
	int number_sent = 1;
	for (int i = 0; i < *size; i++) {
		if ((number_sent % 2 == 0) && (word_count(tmp_text[i]) % 2 == 0)) {
			tmp_text[i] = " \0";
		}
		number_sent++;
	}
	char** new_text = *text;
	int new_size = 0;
	for (int i = 0; i < *size; i++) {
		if (tmp_text[i] != " \0") {
			new_text[new_size] = tmp_text[i];
			new_size++;
		}
	}
	new_text = (char**)realloc(new_text, new_size * sizeof(char*));
	*text = new_text;
	*size = new_size;
}


//___2
typedef struct word {
	char* wrd;
	int count_uppercase;
};

int countcmp(const void* i, const void* j) {
	word* new_i = (word*)i;
	word* new_j = (word*)j;
	return new_i->count_uppercase - new_j->count_uppercase;
}

void word_sort(char** text, int size) {
	for (int i = 0; i < size; i++) {
		char* tmp_string = text[i];
		word* words = (word*)malloc(word_count(tmp_string) * sizeof(word));
		for (int j = 0; j < word_count(tmp_string); j++) {
			words[j].wrd = (char*)malloc(strlen(tmp_string) * sizeof(char));
			words[j].count_uppercase = 0;
		}
		char* separators = (char*)malloc(word_count(tmp_string) * sizeof(char));
		int size_word = -1;
		int count_word = 0;
		for (int j = 0; j < strlen(tmp_string); j++) {
			size_word++;
			words[count_word].wrd[size_word] = tmp_string[j];
			if ((words[count_word].wrd[size_word] >= 65) && (words[count_word].wrd[size_word] <= 90)) {
				words[count_word].count_uppercase++;
			}
			if ((words[count_word].wrd[size_word] == ' ') || (words[count_word].wrd[size_word] == ',') || (words[count_word].wrd[size_word] == '.')) {
				separators[count_word] = words[count_word].wrd[size_word];
				words[count_word].wrd[size_word] = '\0';
				size_word = -1;
				count_word++;
			}
		}
		qsort(words, count_word, sizeof(word), countcmp);
		char* new_string = (char*)malloc(1 * sizeof(char));
		new_string[0] = '\0';
		for (int j = 0; j < count_word; j++) {
			new_string = (char*)realloc(new_string, strlen(new_string) + strlen(words[j].wrd) + 2 * sizeof(char));
			strcat(new_string, words[j].wrd);
			new_string[strlen(new_string) + 1] = '\0';
			new_string[strlen(new_string)] = separators[j];
		}
		free(text[i]);
		text[i] = new_string;
		count_word = 0;
		for (int j = 0; j < count_word; j++) {
			free(words[j].wrd);
		}
		free(words);
	}
}

//___3
void less_then_3(char** text, int size) {
	char** new_text = text;
	for (int i = 0; i < size; i++) {
		char* tmp_string = text[i];
		char* new_string = (char*)malloc(1 * sizeof(char));
		new_string[0] = '\0';
		int size_string = 0;
		int size_word = 0;
		int size_new_string = 0;
		while (tmp_string[size_string] != '\0') {
			if ((tmp_string[size_string] == ',') || (tmp_string[size_string] == '.') || (tmp_string[size_string] == ' ')) {
				if (size_word <= 3) {
					new_string = (char*)realloc(new_string, strlen(new_string) + 13 * sizeof(char));
					strcat(new_string, "Less Then 3");
					new_string[strlen(new_string) + 1] = '\0';
					new_string[strlen(new_string)] = tmp_string[size_string];
					size_new_string += 12;
				}
				else {
					new_string = (char*)realloc(new_string, strlen(new_string) + size_word + 2 * sizeof(char));
					for (int j = 0; j <= size_word; j++) {
						new_string[size_new_string] = tmp_string[size_string - size_word + j];
						size_new_string++;
					}
					new_string[size_new_string] = '\0';
				}
				size_word = -1;
			}
			size_word++;
			size_string++;
		}
		text[i] = new_string;
	} 
}

//___4
bool is_2_number(char* str) {
	int i = 0;
	int count = 0;
	while (str[i] != '.') {
		if ((str[i] >= '0') && (str[i] <= '9')) {
			count++;
		}
		i++;
	}
	if (count >= 2) {
		return 1;
	}
	else {
		return 0;
	}
}

char* substring(char* str) {
	int i = 0;
	int bgn_str = 0;
	int end_str = 0;
	while (str[i] != '.') {
		if ((str[i] >= '0') && (str[i] <= '9')) {
			bgn_str = i;
			break;
		}
		i++;
	}
	i++;
	while (str[i] != '.') {
		if ((str[i] >= '0') && (str[i] <= '9')) {
			end_str = i;
		}
		i++;
	}
	i = 0;
	char* substr = (char*)malloc((end_str - bgn_str + 2) * sizeof(char));
	int subsize = 0;
	while (str[i] != '.') {
		if ((i >= bgn_str) && (i <= end_str)) {
			substr[subsize] = str[i];
			subsize++;
		}
		i++;
	}
	substr[subsize] = '\0';
	return substr;
}

typedef struct sub {
	char* str;
	int size;
} sub;

int sizecmp(const void* i, const void* j) {
	sub* new_i = (sub*)i;
	sub* new_j = (sub*)j;
	return new_j->size - new_i->size;
}

void substrings(char** text, int size) {
	int new_size = 0;
	char** new_text = (char**)malloc((new_size + 1) * sizeof(char*));
	for (int i = 0; i < size; i++) {
		if (is_2_number(text[i])) {
			new_text[new_size] = substring(text[i]);
			new_size++;
			new_text = (char**)realloc(new_text, (new_size + 1) * sizeof(char*));
		}
	}
	sub* subs = (sub*)malloc(new_size * sizeof(sub));
	for (int i = 0; i < new_size; i++) {
		subs[i].str = new_text[i];
		subs[i].size = strlen(new_text[i]);
	}
	qsort(subs, new_size, sizeof(sub), sizecmp);
	printf("Найденные подстроки:\n");
	for (int i = 0; i < new_size; i++) {
		printf("%s\n", subs[i].str);
	}
	for (int i = 0; i < new_size; i++) {
		free(new_text[i]);
	}
	free(new_text);
}

//___MENU
int menu() {
	printf("Введите:\n1 - Если хотите удалить все четные по счету предложения, в которых четное количество слов.\n");
	printf("2 - Если хотите отсортировать все слова в предложениях по возрастанию количества букв в верхнем регистре в слове.\n");
	printf("3 - Если хотите заменить все слова в тексте длина которых не более 3 символов на подстроку “Less Then 3”.\n");
	printf("4 - Если хотите найти в каждом предложении строку максимальной длины, которая начинается и заканчивается цифрой. И вывести найденные подстроки по убыванию длины подстроки.\n");
	printf("0 - Если хотите выйти из программы.\n");
	printf("Операция: ");
	int command = 0;
	scanf_s("%d", &command);
	return command;
}

//___PRINT
void print_text(char** text, int size) {
	printf("Измененный текст:\n");
	for (int i = 0; i < size; i++) {
		printf("%s", text[i]);
	}
	printf("\n");
}

//___FREE
void free_text(char** text, int size) {
	for (int i = 0; i < size; i++) {
		free(text[i]);
	}
	free(text);
}

int main() {
	char** text;
	int size;
	scan_text(&text, &size);
	delete_similar_sents(&text, &size);
	print_text(text, size);
	int command = menu();
	switch (command) {
	case 0:
		return 0;
		break;
	case 1:
		delete_even_sents(&text, &size);
		print_text(text, size);
		break;
	case 2:
		word_sort(text, size);
		print_text(text, size);
		break;
	case 3:
		less_then_3(text, size);
		print_text(text, size);
		break;
	case 4:
		substrings(text, size);
		break;
	default:
		break;
	}
	free_text(text, size);
	return 0;
}