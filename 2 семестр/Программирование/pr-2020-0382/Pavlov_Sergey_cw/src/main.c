#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define mem_add 100
#define RESET "\033[0m"
#define BLUE  "\033[34m"


// Прием предложения
char* get_sentence(){

    char* tmp_sent = malloc(100*sizeof(char));
    int tmp_mem = 50;
    int len=0;
    char ch;

    while(1){

        ch = getchar();
        //printf("CH: [%c]\t", ch);
        if (ch == '\n')
            return NULL;

        tmp_sent[len] = ch;
        len += 1;

        if (ch == '.') break;

        if (len>=tmp_mem){
            tmp_mem += mem_add;
            tmp_sent = realloc(tmp_sent, tmp_mem);
        }

    }

    if(tmp_sent[0] == ' '){
        char* r_tmp_sent = malloc((tmp_mem-1)*sizeof(char));

        for(int j=0;j < len;j++){

            r_tmp_sent[j] = tmp_sent[j+1];

        }
        r_tmp_sent[len-1] = '\0';
        return r_tmp_sent;
    }
    else {
        tmp_sent[len] = '\0';
        return tmp_sent;
    }
}


_Bool is_similar_sents(char* strA, char* strB) {
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

_Bool check_similar(char** text, char* sentence, int text_sentences){
    int i;
    for (i=0;i<=text_sentences-1;i++){
        //printf("Text[%d]: [%s] Sent: [%s]\n", i,text[i],sentence);
        if (is_similar_sents(text[i], sentence)){
            return 0;
        }
    }
    return 1;
}

void print_text(char** text, int text_sentences){
    for (int k=0;k<text_sentences; k++){
        if (text[k][0] != '\0'){
            printf("%s ",text[k]);
            free(text[k]);
        }
    }
    printf("\n");
    free(text);
}

void upper_transform(char** text, int text_sentences){
    unsigned int len_str;
    int num;
    for (int i=0;i<text_sentences;i++){
        len_str = strlen(text[i]);
        text[i][0] = (char)toupper(text[i][0]);

        for(int j=1;j<len_str;j++){
            num = ((int) text[i][j]);
            if ((num<91)&&(num>64)){
                //printf("CH: [%c]\n", text[i][j]);
                text[i][j] = ((char) tolower(text[i][j]));
            }

        }

    }
}

unsigned int how_words(char* sentence){
    unsigned int sent_len = strlen(sentence);
    unsigned int words=0;
    char ch;
    char pre_ch;
    for(int i=0;i<(sent_len-1);i++){
        ch = sentence[i];
        if (((ch == ' ')||(ch == ','))&&(pre_ch != ','))
            words += 1;
        pre_ch = ch;
    }
    words += 1;
    return words;
}

void delete_even_word(char** text, int text_sentences){
    for (int i=0;i<text_sentences;i++){
        //printf("Sent: [%s]Words: %i\n",text[i], how_words(text[i]));

        if (how_words(text[i])%2 == 0)
            text[i][0] = '\0';

    }
}

int is_vowel(char c) {
    switch(tolower(c)){
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
        case 'y':
            return 1;
        default:
            return 0;
    }
}


int how_vowels(char* sentence){
    int vowels = 0;
    unsigned int str_len = strlen(sentence);
    int word = 1;
    char ch,pre_ch;

    for (int i=0;i<str_len;i++){

        // (!!!) СЛОВА
        ch = sentence[i];
        if (((ch == ' ')||(ch == ','))&&(pre_ch != ','))
            word += 1;
        pre_ch = ch;
        if ((is_vowel(sentence[i]) == 1)&&(word%2==1))
            vowels += 1;
    }
    return vowels;
}


int compare_vowel(const void *a, const void *b)
{
    char **x = (char**)a;
    char **y = (char**)b;

    int xx = how_vowels(*x);
    int yy = how_vowels(*y);

    return (yy-xx);
}
/*
char** split_words(char* sentence){
    unsigned int str_len = strlen(sentence);
    unsigned int words = how_words(sentence);
    char** words_mass = (char**) malloc(100*sizeof(char*));
    int word=0;
    char ch,pre_ch;
    int j=0,i=0;

    for(i=0;i<strlen;i++){
        char* tmp_str = malloc(str_len*sizeof(char));

        ch = sentence[i];

        if ((ch != ' ')&&(ch != ',')&&(ch != '.')){
            tmp_str[j] = ch;
            printf("CH: %c\n", tmp_str[j]);
        }

        if ((ch == ' ')||(ch == ',')) {
            tmp_str[j] = '\0';
            printf("STR %s\n", tmp_str);
            words_mass[word] = tmp_str;
            j = 0;
            word += 1;
        }
        if (ch=='.') {
            tmp_str[j] = '\0';
            break;
        }
    }



    printf("Word[0]: %s\n", words_mass[0]);
    printf("Word[1]: %s\n", words_mass[1]);
    printf("Word[2]: %s\n", words_mass[2]);
    printf("Word[3]: %s\n", words_mass[3]);
    return words_mass;
}
*/

int* get_indexes(char* sentence){

    unsigned int words = how_words(sentence);


    int* ans = malloc(10*sizeof(int));
    unsigned int sent_len = strlen(sentence);
    char ch, pre_ch;
    int word=0;

    ans[0] = 0;
    ans[1] = 0;
    ans[2] = 0;
    ans[3] = 0;

    if (words%2 == 0) {
        unsigned int first_word_i = (words/2)-1;
        unsigned int second_word_i = (words/2);
        for (int i = 0; i < sent_len; i++) {

            ch = sentence[i];
            if (((ch == ' ') || (ch == ',')) && (pre_ch != ','))
                word += 1;

            if ((word == first_word_i) && ((ch == ' ') || (ch == ','))) {
                ans[0] = i + 1;
                int i_tmp = i;

                while (1) {
                    ch = sentence[i_tmp + 1];

                    if ((ch == ' ') || (ch == ',')) {
                        ans[1] = i_tmp;
                        break;
                    }

                    i_tmp += 1;

                }

            }

            if ((word == second_word_i) && ((ch == ' ') || (ch == ','))) {
                ans[2] = i + 1;
                int i_tmp = i;

                while (1) {
                    ch = sentence[i_tmp + 1];

                    if ((ch == ' ') || (ch == ',')) {
                        ans[3] = i_tmp;
                        break;
                    }

                    i_tmp += 1;

                }

            }

            pre_ch = ch;
        }
    }
    else{
        unsigned int first_word_i = (words/2);
        unsigned int second_word_i = (words+1/2);
        for (int i = 0; i < sent_len; i++) {

            ch = sentence[i];
            if (((ch == ' ') || (ch == ',')) && (pre_ch != ','))
                word += 1;

            if ((word == first_word_i) && ((ch == ' ') || (ch == ','))) {
                ans[0] = i + 1;
                int i_tmp = i;

                while (1) {
                    ch = sentence[i_tmp + 1];

                    if ((ch == ' ') || (ch == ',')) {
                        ans[1] = i_tmp;
                        break;
                    }

                    i_tmp += 1;

                }

            }

            if ((word == second_word_i) && ((ch == ' ') || (ch == ','))) {
                ans[2] = i + 1;
                int i_tmp = i;

                while (1) {
                    ch = sentence[i_tmp + 1];

                    if ((ch == ' ') || (ch == ',')) {
                        ans[3] = i_tmp;
                        break;
                    }

                    i_tmp += 1;

                }

            }

            pre_ch = ch;
        }
    }


    return ans;
    }

_Bool check_lower(char* sentence, int* indexes, int multi){
    char ch;

    if (multi == 1){
        int i = indexes[0];
        _Bool tmp1=1;
        _Bool tmp2=1;
        while (i<=indexes[1]){
            ch = sentence[i];
            int num = (int) ch;
            if ((num<91)&&(num>64)) {
                tmp1 = 0;
                break;
            }
            i += 1;
        }
        i = indexes[2];
        while (i<=indexes[3]){
            ch = sentence[i];
            int num = (int) ch;
            if ((num<91)&&(num>64)) {
                tmp2 = 0;
                break;
            }
            i += 1;
        }

        if (tmp1 == tmp2)
            return 1;
        else return 0;


    }
    else if (multi == 0){
        int i = indexes[0];
        _Bool tmp1=1;
        while (i<=indexes[1]){
            ch = sentence[i];
            int num = (int) ch;
            if ((num<91)&&(num>64)) {
                return 0;
            }
            i += 1;
        }
        return tmp1;
    }

}

void moddiff_print(char* sentence, int* indexes){

    unsigned len = strlen(sentence);
    int words = how_words(sentence);

    char ch;
    int word=0;

    for (int i=0;i<len;i++){

        ch = sentence[i];

        if (i==indexes[0]) printf("%s", BLUE);

        if (i==indexes[1]+1) printf("%s", RESET);

        if (words%2 == 0) {
            if (i == indexes[2]) printf("%s", BLUE);

            if (i == indexes[3] + 1) printf("%s", RESET);
        }
        printf("%c", ch);
    }
    printf(" ");
}

void lower_words_display(char** text, int text_sentences){

    unsigned int sent_len;
    unsigned int words;
    char ch;
    int* indexes;
    // Перебор предлржений
    for (int i=0;i<text_sentences;i++){

        sent_len = strlen(text[i]);
        words = how_words(text[i]);
        //EVEN
        if ((words % 2)== 0){
            indexes = get_indexes(text[i]);
            // если прописные то
            if ((check_lower(text[i], indexes, 1))==1){
                moddiff_print(text[i], indexes);
                free(text[i]);
            }
            else{
                printf("%s ",text[i]);
                free(text[i]);
            }


        }
        //ODD
        if ((words % 2) != 0){
            indexes = get_indexes(text[i]);
            // если прописные то
            if ((check_lower(text[i], indexes, 1))==1){
                moddiff_print(text[i], indexes);
                free(text[i]);
            }
            else{
                printf("%s ",text[i]);
                free(text[i]);
            }

        }
    }
    free(text);
}

int main() {
    // доп
    //инициализация
    char **text = malloc(200 * sizeof(char *));
    char *sentence;
    int text_sentences = 0;
    int text_mem = 200;
    int i = 0;
    //Цикл приема и пред-обработки

    while (1) {
        sentence = get_sentence();
        // printf("[STR]: %s\n", sentence);


        if (sentence == NULL) break;
        else {
            // Добавление памяти
            if (text_sentences >= text_mem) {
                //printf("(!) Mem added!\n");
                text_mem += mem_add;
                text = realloc(text, (text_mem * sizeof(char *)));
            }
            // Проверка на одинаковые и запись в text
            if ((check_similar(text, sentence, text_sentences) != 0) || (text_sentences == 0)) {
                //printf(" |--> Added: %s\n", sentence);
                text[text_sentences] = sentence;
                text_sentences += 1;
            }

        }
    }

    int command;


    printf("Выбор действия:\n");
    printf("  {1} - Сделать первую букву в каждом предложении заглавной, а остальные символы в предложении прописными.\n");
    printf("  {2} - Удалить предложения состоящие из четного кол-ва слов.\n");
    printf("  {3} - Отсортировать предложения по сумме количеств гласных букв в каждом втором слове.\n");
    printf("  {4} - Вывести на экран все предложения, в которых в середине слова встречаются слова, состоящие из прописных букв.\n");
    printf("\n  {0} - Завершить программу.\n");

    printf("Command: ");

    scanf("%d", &command);
    printf("\n");

    //Выбор команды
    switch (command) {
        case 0:
            break;
        case 1:
            upper_transform(text, text_sentences);
            print_text(text, text_sentences);
            break;
        case 2:
            delete_even_word(text, text_sentences);
            print_text(text, text_sentences);
            break;
        case 3:
            qsort(text,text_sentences,sizeof(char*),compare_vowel);
            print_text(text, text_sentences);
            break;
        case 4:
            lower_words_display(text, text_sentences);
            break;
        default:
            break;


    }
    return 0;
}