#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
int get_size(char*** text); // функция подсчета количества предложений во входящем тексте
int new_size(char*** text, int size); // функция удаляет вопросительные предложения 
char* get_sentence(); // функция считывает и возвращает предложение, при неудаче возвращает NULL
char last_ch(char* sentence);
void free_text(char*** text, int size); // освобождение памяти выделенной под текст
int main() {
    setlocale(LC_ALL, "ru");
    char** text; //массив предложений (текст)
    int amount_of_sentences = get_size(&text); // размер текста - передаем текст в функцию 
    int new_amount_of_sentences = new_size(&text, amount_of_sentences);
    for (int i = 0; i < new_amount_of_sentences; i++)
        printf("%s", text[i]);
    printf("Количество предложений до %i и количество предложений после %i\n", amount_of_sentences, new_amount_of_sentences-1);
    free_text(&text, amount_of_sentences);
    return 0;
}
int get_size(char*** text) {
    int l = 50; // количество выделяемой памяти для динамического массива
    char** t = (char**) malloc(l*sizeof(char*)); //выделяем память для временной переменной t 
    if (t != NULL) {            // если удалось выделить память, то
        *text = t;              // используем ее для записи текста
        char* sentence; // предложение (массив чаров)
        int amount_of_sentences = 0;
        const char* last_sentence = "Dragon flew away!\n"; // терминальное предложение
        for (sentence = get_sentence(); strcmp(sentence, last_sentence) != 0; sentence = get_sentence()) {
            if (sentence == NULL) {                   // если предложения нет, то текст является пустым
                free_text(text, amount_of_sentences); //поэтому чистим динамическую память и возвращаем 0
                return 0;
            }
            (*text)[amount_of_sentences++] = sentence;
            if (amount_of_sentences == l - 1) { // если не хватает динамической памяти
                l += l;                         // расширяем ее 
                t = (char**) realloc(t, l*sizeof(char*));
                if (t != NULL)
                    *text = t; // если получилось расширить используем для записи текста
                else {
                    free_text(text, amount_of_sentences); //если нет то чистим динамическую память и возвращаем 0
                    return 0;
                }
            }
        }
        (*text)[amount_of_sentences] = sentence;
        return amount_of_sentences;
    }
    return 0; // если не удалось выделить память, то возвращаем 0
}
char* get_sentence() {
    int l = 50; // количество выделяемой памяти для динамического массива
    char* t = (char*) malloc(l*sizeof(char)); // выделяем память под предложение
    if (t != NULL) {                // если удалось выделить память, то
        char* sentence = t;         // используем ее для записи предложения
        char ch;
        int i = 0;
        do {// считываем первый символ предложения и продолжаем считывать до тех пор пока не найдем букву, тем самым избавляемся от табуляции
            ch = getchar();
        } while ((ch == ' ') || (ch == '\n') || (ch == '\t'));
        while ((ch != '.') && (ch != ';') && (ch != '?') && (ch != '!')) {
            if (i == l - 3) { //так как предложение обязательно оканчивается на '\n' и '\0' сравниваем i с (l - 1) - 2
                l += l;                         // расширяем память если необходимо 
                t = (char*)realloc(t, l * sizeof(char));
                if (t != NULL)
                    sentence = t; // если получилось расширить используем для записи предложения
                else {
                    free(sentence); //если нет то чистим динамическую память и возвращаем NULL
                    return NULL;
                }
            }
            sentence[i++] = ch; //считываем символы и добавялем их в массив до тех пор пока не считаем символ окончания предложения
            ch = getchar();
        }
        sentence[i++] = ch;
        sentence[i++] = '\n'; //добавим к предложению знак переноса строки
        sentence[i] = '\0'; //добавим нуль терминатор, окончив строку
        return sentence;
    }
    return NULL;
}
int new_size(char*** text, int size) {
    char** t = (char**) malloc(size * sizeof(char*));
    if (t != NULL) {
        char** new_text = t;
        int new_amount_of_sentences = 0;
        for (int i = 0; i < size+1; i++) {
            if (last_ch((*text)[i]) != '?')
                new_text[new_amount_of_sentences++] = (*text)[i];
            else
                free((*text)[i]);
        }
        free(*text);
        *text = new_text;
        return new_amount_of_sentences;
    }
    return 0;
}
char last_ch(char* sentence) {
    char last_ch = sentence[strlen(sentence) - 2];
    return last_ch;
}
void free_text(char*** text, int size) { // функция освобождения памяти
    for (int i = 0; i < size; i++)
        free((*text)[i]);
    free(*text);
}
