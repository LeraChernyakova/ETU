#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define defaultN 5
#define DefaultColor "\033[0m"
#define Blue "\033[46;31m"

// Структуры

typedef struct {
    char *symbols;
    char end;
    int size, memorySize;
} Word;

typedef struct {
    Word *words;
    int size, memorySize;
} Sent;

typedef struct {
    Sent *sents;
    int size, memorySize;
} Text;


void freeW(Word *word) {
    free(word->symbols);
    word->size = 0, word->memorySize = 0;
}

void freeSent(Sent *sentence) {
    for (int i = 0; i < sentence->size; ++i)
        freeW(&sentence->words[i]);
    free(sentence->words);
    sentence->size = 0, sentence->memorySize = 0;
}

void rmSent(Text *txt, int index) {
    if (index < 0 || index >= txt->size)
        return;
    freeSent(&txt->sents[index]);
    memmove(&txt->sents[index], &txt->sents[index + 1], (txt->size - index - 1) * sizeof(Sent));
    txt->sents = realloc(txt->sents, sizeof(Sent) * (--txt->size));
    if (txt->sents == NULL) {
        printf("\033[0;31mCouldn't reallocate memory for sents array in text at %p to size %d\n", txt, txt->size);
        exit(0);
    }
    txt->memorySize = txt->size;
}

void freeText(Text *txt);

void printWord(Word* word) {
    for(int i = 0; i < word->size; i++)
        printf("%c", word->symbols[i]);
    if (word->end)
        printf("%c", word->end);
}

void printText(Text *txt){
    for (int i = 0; i < txt->size; i++)
        for (int j = 0; j < txt->sents[i].size; j++){
            printWord(&txt->sents[i].words[j]);
            printf(" ");
        }
    printf("\n");
}

void initW(Word *word) {
    word->size = 0;
    word->end = 0;
    word->memorySize = defaultN;
    word->symbols = malloc(word->memorySize * sizeof(char));
    if (word->symbols == NULL) {
        printf("\033[0;31mCouldn't allocate memory for symbols array in word at %p to size %d\n", word, word->memorySize);
        exit(0);
    }
}

void appChar(Word *word, char c) {
    if (word->size >= word->memorySize) {
        word->symbols = realloc(word->symbols, sizeof(char) * (word->memorySize += defaultN));
        if (word->symbols == NULL) {
            printf("\033[0;31mCouldn't reallocate memory for symbols array in word at %p to size %d\n",
                   word, word->memorySize);
            exit(0);
        }
    }
    word->symbols[word->size++] = c;
}

void initS(Sent *sentence) {
    sentence->size = 0;
    sentence->memorySize = defaultN;
    sentence->words = malloc(sentence->memorySize * sizeof(Word));
    if (sentence->words == NULL) {
        printf("\033[0;31mCouldn't allocate memory for words array in sentence at %p to size %d\n", sentence,
               sentence->memorySize);
        exit(0);
    }
}

int sentEql(Sent *first, Sent *scnd) {
    if (first->size != scnd->size)
        return 0;
    for (int i = 0; i < first->size; ++i) {
        if (first->words[i].size != scnd->words[i].size || first->words[i].end != scnd->words[i].end)
            return 0;
        for (int j = 0; j < first->words[i].size; ++j)
            if (tolower(first->words[i].symbols[j]) != tolower(scnd->words[i].symbols[j]))
                return 0;
    }
    return 1;
}

Word *newW(Sent *sentence) {
    if (sentence->size >= sentence->memorySize) {
        sentence->words = realloc(sentence->words, sizeof(Word) * (sentence->memorySize *= 2));
        if (sentence->words == NULL) {
            printf("\033[0;31mCouldn't reallocate memory for words array in sentence at %p to size %d\n", sentence,
                   sentence->memorySize);
            exit(0);
        }
    }
    initW(&sentence->words[sentence->size]);
    return &sentence->words[sentence->size++];
}


void removeDoubleSent(Text *txt) {
    for (int i = 0; i < txt->size;i++)
        for (int j = txt->size-1; j > i; --j)
            if (sentEql(&txt->sents[i], &txt->sents[j]))
                rmSent(txt, j);
}



const char *funcN[5] = {
        "Преобразовать предложения так, чтобы каждое первое слово в нем начиналось с заглавной буквы, а остальные символы были прописными",
        "Отсортировать предложения по сумме количеств гласных букв в каждом втором слове",
        "Удалить все предложения, состоящие из четного количества слов",
        "Вывести на экран все предложения, в которых в середине предложения встречаются слова, состоящие из прописных букв",
        "Выйти",
};

void editSent(Text *txt){
    for( int i = 0; i < txt->size;i++){
        for( int j = 0; j < txt->sents[i].size ;j++){
            txt->sents[i].words[j].symbols[0] = toupper(txt->sents[i].words[j].symbols[0]);
        }
    }
    printText(txt);
}

char vowels[] = {'a', 'e', 'u', 'i', 'o', 'y'};

int countVowels(Sent* sent) {
    int result = 0;
    for (int i = 1; i < sent->size; i += 2)
        for (int j = 0; j < sent->words[i].size; j++)
            for (int k = 0; k < 6; k++)
                if (sent->words[i].symbols[j] == vowels[k]) {
                    result++;
                    break;
                }
    return result;
}

int compFunc(const void* va, const void* vb) {
    Sent *a = (Sent*) va;
    Sent *b = (Sent*) vb;
    return countVowels(a) - countVowels(b);
}

void sortSent(Text *txt){
    qsort(txt->sents, txt->size, sizeof(Sent), compFunc);
    printText(txt);
}

void rmEventSent(Text *txt) {
    for (int i = txt->size - 1; i > -1; --i)
        if (txt->sents[i].size % 2 == 0)
            rmSent(txt, i);
    printText(txt);
}


void printSentCenter(Text *txt){
    for(int i = 0; i < txt->size; i++){
        int numbUpper = 0; // количество символов в верхнем рег.
        int k = 0; // количество символов в общем
        int lenString = txt->sents[i].size;
        int indexW;
        if (lenString%2 != 0){
            indexW = lenString/2;
            while(k < txt->sents[i].words[indexW].size){
                if(isupper(txt->sents[i].words[indexW].symbols[k])){
                    numbUpper++;
                }
                k++;
            }
            if(numbUpper == k){
                for(int j = 0; j < indexW; j++){
                    printWord(&txt->sents[i].words[j]);
                    printf(" ");
                }
                printf("%s", Blue);
                printWord(&txt->sents[i].words[indexW]);
                printf("%s", DefaultColor);
                printf(" ");
                for (int j = indexW + 1; j < txt->sents[i].size; j++){
                    printWord(&txt->sents[i].words[j]);
                    printf(" ");
                }
            }
        } else {
            indexW = lenString/2;
            while(k < txt->sents[i].words[indexW-1].size){
                if(isupper(txt->sents[i].words[indexW-1].symbols[k])){
                    numbUpper++;
                }
                k++;
            }
            int blue1 = (numbUpper == k);
            numbUpper = 0, k = 0;
            while(k < txt->sents[i].words[indexW].size){
                if(isupper(txt->sents[i].words[indexW].symbols[k])){
                    numbUpper++;
                }
                k++;
            }
            int blue2 = (numbUpper == k);
            if (blue1 || blue2) {
                for(int j = 0; j < indexW - 1; j++){
                    printWord(&txt->sents[i].words[j]);
                    printf(" ");
                }
                if (blue1)
                    printf("%s", Blue);
                printWord(&txt->sents[i].words[indexW-1]);
                printf("%s", DefaultColor);
                printf(" ");
                if (blue2)
                    printf("%s", Blue);
                printWord(&txt->sents[i].words[indexW]);
                printf("%s", DefaultColor);
                printf(" ");
                for(int j = indexW + 1; j < txt->sents[i].size; j++){
                    printWord(&txt->sents[i].words[j]);
                    printf(" ");
                }
            }
        }
    }
}

void initText(Text *txt) {
    txt->size = 0;
    txt->memorySize = defaultN;
    txt->sents = malloc(txt->memorySize * sizeof(Sent));
}

Sent *newSent(Text *txt) {
    if (txt->size >= txt->memorySize) {
        txt->sents = realloc(txt->sents, sizeof(Sent) * (txt->memorySize *= 2));
        if (txt->sents == NULL) {
            printf("\033[0;31mCouldn't reallocate memory for sents array in text at %p to size %d\n", txt, txt->memorySize);
            exit(0);
        }
    }
    initS(&txt->sents[txt->size]);
    return &txt->sents[txt->size++];
}

void readText(Text *result) {
    char c;
    Sent *currSent = newSent(result);
    Word *currentWord = newW(currSent);
    do {
        c = getchar();
        if (c == ' ') {
            if (currentWord->size) {
                currentWord->end = 0;
                currentWord = newW(currSent);
            }
        } else if (c == ',') {
            currentWord->end = ',';
            currentWord = newW(currSent);
        } else if (c == '.') {
            currentWord->end = '.';
            currSent = newSent(result);
            currentWord = newW(currSent);
        } else if (c && c != '\n')
            appChar(currentWord, c);
    } while (c && c != '\n');
    if (c == '\n' && !currentWord->size)
        freeSent(&result->sents[--result->size]);
}

void freeText(Text *txt) {
    for (int i = 0; i < txt->size; ++i)
        freeSent(&txt->sents[i]);
    free(txt->sents);
    txt->size = 0, txt->memorySize = 0;
}

int main() {
    Text txt;
    initText(&txt);
    printf("Введите текст, состоящий из цифр и латинских букв\n\n");
    readText(&txt);
    printf("\n");
    printf("\nВведенный текст прочитан\n");
    printf("\n");
    removeDoubleSent(&txt);
    printf("\n");
    printf("\nДублирующиеся предложения удалены\n");
    printText(&txt);
    int numb;
    do{
        numb = 0;
        printf("\n");
        for (int i = 0; i < 5; ++i) {
            printf("%d: %s\n", i + 1, funcN[i]);
        }
        while (numb < 1 || numb > 5) {
            printf("Введите номер команды (1-5):\n");
            scanf("%d", &numb);
        }
        numb--;
        switch (numb){
            case 0:
                editSent(&txt);
                printf("Выполнено: %s\n", funcN[numb]);
                break;
            case 1:
                sortSent(&txt);
                printf("Выполнено: %s\n", funcN[numb]);
                break;
            case 2:
                rmEventSent(&txt);
                printf("Выполнено: %s\n", funcN[numb]);
                break;
            case 3:
                printSentCenter(&txt);
                printf("Выполнено: %s\n", funcN[numb]);
                break;
            case 4:
                break;
            default:
                break;
        }
    }while (numb != 4);
    freeText(&txt);
    printf("Работа программы законченафнаф\n");
    return 0;
}
