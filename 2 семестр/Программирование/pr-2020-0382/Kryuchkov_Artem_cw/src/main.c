#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

#include "textStructures.h"
#include "stringsOperations.h"
#include "input.h"
#include "output.h"

int main() {
    setlocale(LC_ALL, "");
    wprintf(L"Для начала работы с программой нужно ввести текст\n");
    struct Text text = readText();
    text = deleteRepeatedSentences(text);
    wchar_t key = L'1';
    wprintf(L"Чтобы изменить все слова в тексте заканчивающиеся на “ться” так чтобы они заканчивались на “тся” и наоборот, а затем вывести полученный текст, введите \"1\".\n"
            "Чтобы вывести все предложения в которых встречается второе слово первого предложения, введите \"2\".\n"
            "Чтобы отсортировать предложения по возрастанию количества слов в предложении, а затем вывести полученный текст, введите \"3\".\n"
            "Чтобы удалить все предложения в которых больше 10 слов, а затем вывести полученный текст, введите \"4\".\n"
            "Для выхода из программы введите любой другой символ.\n"
    );
    while (wcschr(L"1234", key) != NULL) {
        key = fgetwc(stdin);
        fgetwc(stdin);
        switch (key) {
            case L'1':
                text = changeEnding(text);
                printText(text);
                break;
            case L'2':
                printSentsWithSecondWordFirstSent(text);
                break;
            case L'3':
                qsort(text.sentences, text.n, sizeof(struct Sentence *), compareSentencesByWords);
                printText(text);
                break;
            case L'4':
                text = deleteBigSentences(text);
                printText(text);
                break;
            default:
                wprintf(L"Выход из программы.\n");
                break;
        }
    }
    for (int i = 0; i < text.n; ++i) {
        free(text.sentences[i]->words);
        free(text.sentences[i]);
    }
    free(text.sentences);
    return 0;
}
