#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct numbers_with_sentences {
    char *sentence;
    int number;
};

char **delete_word(char **text, int *sent_count) {
    char *word = malloc(20);
    int word_size = 20;
    int word_len = 0;
    char c = ' ';
    while (c != '\n') {
        c = (char) getchar();
        word[word_len] = c;
        if (word[word_len] == '\n') {
            word[word_len] = '\0';
            break;
        }
        word_len++;
        if (word_len == word_size) {
            word_size += 20;
            word = realloc(word, word_size);
        }
    }
    char *substr_pointer;
    int k;
    int j;
    for (int i = 0; i < *sent_count; i++) {
        while ((substr_pointer = strstr(text[i], word)) != NULL) {
            if (*(substr_pointer + strlen(word)) == '.' && (substr_pointer - text[i]) != 0) {
                for (j = 0; j < strlen(word) + 1; j++) {
                    for (k = substr_pointer - text[i] - 1; k < strlen(text[i]); k++) {
                        text[i][k] = text[i][k + 1];
                    }
                }
            } else {
                for (j = 0; j < strlen(word) + 1; j++) {
                    for (k = substr_pointer - text[i]; k < strlen(text[i]); k++) {
                        text[i][k] = text[i][k + 1];
                    }
                }

            }
            text[i][k] = '\0';
        }
        if (text[i][0] == '\0') {
            for (int n = i; n < *sent_count - 1; n++) {
                text[n] = text[n + 1];
            }
            i -= 1;
            *sent_count = *sent_count - 1;
            text = realloc(text, *sent_count * sizeof(char *));

        }

    }
    return text;
}


int letters_comparator(const void *a, const void *b) {
    char *arr1 = (char *) a;
    char *arr2 = (char *) b;

    return *arr1 - *arr2;
}


char **upper_letters_sort(char **text, int *sent_count, int *new_sent_count) {
    int arr_size = 30;
    char **upper_letters = malloc(arr_size);
    for (int i = 0; i < *sent_count; i++) {
        int letter_counter = 0;
        char *sentence_letters = malloc(20);
        int sentence_letters_size = 20;
        for (int j = 0; j < strlen(text[i]) - 1; j++) {
            if (isupper(text[i][j])) {
                sentence_letters[letter_counter] = text[i][j];
                letter_counter++;
                if (sentence_letters_size == letter_counter) {
                    sentence_letters_size += 20;
                    sentence_letters = realloc(sentence_letters, sentence_letters_size);
                }
            }
        }

        sentence_letters[letter_counter] = '\0';
        if (i == arr_size) {
            arr_size += 30;
            upper_letters = realloc(upper_letters, arr_size);
        }
        if (sentence_letters[0] != '\0') {
            upper_letters[*new_sent_count] = sentence_letters;
            qsort(upper_letters[*new_sent_count], letter_counter, sizeof(char), letters_comparator);
            *new_sent_count += 1;
        }
    }
    return upper_letters;
}


char *input_sentence() {
    int sentence_size = 100, sym_count = 0;
    char sym = 0;
    int n_counter = 0;
    char *sentence = malloc(sentence_size * sizeof(char));
    while (sym != '.') {
        sym = (char) getchar();
        if (sym == '\n') {
            n_counter++;
            if (n_counter == 2) {
                free(sentence);
                return "end_of_input";
            }
        } else {
            sentence[sym_count] = sym;
            sym_count += 1;
            n_counter = 0;
            if (sym_count == sentence_size) {
                sentence_size = sentence_size + 100 * (int) sizeof(char);
                sentence = realloc(sentence, sentence_size);
            }
        }
    }
    sentence[sym_count + 1] = '\0';
    return sentence;

}


char **text_without_repeats(char **text, int *sent_count) {
    for (int i = 0; i < *sent_count - 1; i++) {
        for (int j = i + 1; j < *sent_count; j++) {
            if (!strcasecmp(text[i], text[j])) {
                for (int n = j; n < *sent_count - 1; n++)
                    text[n] = text[n + 1];
                *sent_count -= 1;
                j -= 1;
            }
        }
    }
    return text;
}


char *no_spaces(char *sentence) {
    if (strcmp(sentence, "end_of_input") != 0) {
        while (sentence[0] == ' ' || sentence[0] == '\t') {
            int i;
            for (i = 0; i < strlen(sentence) - 1; i++) {
                sentence[i] = sentence[i + 1];
            }
            sentence[i] = '\0';
        }
        sentence = realloc(sentence, strlen(sentence));
    }
    return sentence;
}


void print_menu() {
    printf("Выберите желаемую опцию из перечисленных\n"
           "1.Во всем тексте удалить слово введенное пользователем. Если после удаления в предложении не останется слов, его необходимо удалить.\n"
           "2.Для каждого предложения вывести все заглавные буквы в лексикографическом порядке.\n"
           "3.Отсортировать предложения по среднему арифметическому чисел в предложении. Число - слово состоящее только из цифр.\n"
           "4.Удалить все предложения в которых нет строчных букв.\n"
           "5.Выйти из программы\n\n");
}


char **input_text(int *size) {
    int text_size = 10;
    int sent_count = 0;
    char **text = malloc(text_size * sizeof(char *));
    while (1) {
        text[sent_count] = input_sentence();
        text[sent_count] = no_spaces(text[sent_count]);
        if (!strcmp(text[sent_count], "end_of_input"))
            break;
        sent_count += 1;
        if (sent_count == text_size) {
            text_size = text_size + 10 * (int) sizeof(char *);
            text = realloc(text, text_size);
        }
    }
    *size = sent_count;
    return text;
}


void print_text(char **text, int sent_count) {
	printf("\n");
    for (int i = 0; i < sent_count; i++)
        printf("%s\n", text[i]);
}

void free_text(char **text, int sent_count) {
    for (int i = 0; i < sent_count; i++)
        free(text[i]);
    free(text);
}


void print_and_free_letters_and_text(char **upper_letters, int new_sent_count, char **text, int sent_count) {
    for (int i = 0; i < new_sent_count; i++)
        printf("%s\n", upper_letters[i]);
    for (int i = 0; i < new_sent_count; i++)
        free(upper_letters[i]);
    free(upper_letters);
    for (int i = 0; i < sent_count; i++)
        free(text[i]);
    free(text);
}

int numbers_comparator(const void *a, const void *b) {
    struct numbers_with_sentences *a1 = (struct numbers_with_sentences *) a;
    struct numbers_with_sentences *a2 = (struct numbers_with_sentences *) b;

    return a1->number - a2->number;
}

void sort_by_numbers(char **text, int sent_count) {
    float avg_numbers_array[sent_count];
    float no_numbers = 0;
    float num_counter = 0, num = 0;
    float sum = 0;
    int flag;
    for (int i = 0; i < sent_count; i++) {
        flag = 0;
        for (int j = 0; j < strlen(text[i]); j++) {
            if (isalpha(text[i][j]))
                flag = 0;
            if (isdigit(text[i][j]) && (flag == 1 || j == 0)) {
                num = num * 10 + text[i][j] - 48;
                flag = 1;
            }
            if (text[i][j] == ' ' || text[i][j] == ',' || text[i][j] == '.') {
                if (flag == 1) {
                    sum += num;
                    num_counter += 1;
                    num = 0;
                } else
                    flag = 1;
            }
        }
        if (num_counter != 0) {
            avg_numbers_array[i] = sum / num_counter;
            sum = 0;
            num_counter = 0;
        } else {
            avg_numbers_array[i] = -(sent_count) + no_numbers;
            no_numbers += 1;
        }
    }

    struct numbers_with_sentences final_array[sent_count];
    for (int i = 0; i < sent_count; i++) {
        final_array[i].sentence = text[i];
        final_array[i].number = avg_numbers_array[i];
    }
    qsort(final_array, sent_count, sizeof(struct numbers_with_sentences), numbers_comparator);
    for (int i = 0; i < sent_count; i++) {
        printf("%s\n", final_array[i].sentence);
    }

}

void delete_without_lowers(char **text, int *sent_len) {
    int i, j;
    for (i = 0; i < *sent_len; i++) {
        int flag = 0;
        for (j = 0; j < strlen(text[i]); j++) {
            if (islower(text[i][j]))
                flag = 1;
        }
        if (flag == 0) {
            for (int n = i; n < *sent_len - 1; n++) {
                text[n] = text[n + 1];
            }
            i -= 1;
            *sent_len -= 1;
            text = realloc(text, *sent_len * sizeof(char *));
        }


    }


}


int main() {
    char **text;
    char **upper_letters;
    int sent_count, prog_done = 0, choice, new_sent_count;
    printf("Введите текст для обработки. Вы можете вводить предложения с новой строки. Для окончания ввода нажмите 2 раза клавишу Enter.\n\n");
    text = input_text(&sent_count);
    text = text_without_repeats(text, &sent_count);
    text = realloc(text, sent_count * sizeof(char *));
    print_menu();
    scanf("%d", &choice);
    fgetc(stdin);

    while (prog_done != 1) {

        switch (choice) {
            case 1:
                printf("Введите слово, которое вы хотите удалить из текста:\n");
                text = delete_word(text, &sent_count);
                print_text(text, sent_count);
                free_text(text, sent_count);
                prog_done = 1;
                break;

            case 2:
                upper_letters = upper_letters_sort(text, &sent_count, &new_sent_count);
                print_and_free_letters_and_text(upper_letters, new_sent_count, text, sent_count);
                prog_done = 1;
                break;
            case 3:
                sort_by_numbers(text, sent_count);
                free_text(text, sent_count);
                prog_done = 1;
                break;
            case 4:
                delete_without_lowers(text, &sent_count);
                print_text(text, sent_count);
                free_text(text, sent_count);
                prog_done = 1;
                break;
            case 5:
                prog_done = 1;
                break;
            default:
                printf("Некорректный номер опции,попробуйте снова\n");
                scanf("%d", &choice);
                fgetc(stdin);
        }

    }

    return 0;
}

