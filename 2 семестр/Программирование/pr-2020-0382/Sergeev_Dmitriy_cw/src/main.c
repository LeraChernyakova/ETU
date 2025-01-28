#include "structures.h"
#include "text_changing.h"
#include "input_funcs.h"
#include "output_funcs.h"

#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

int Menu(Text MyText);

int main() {
    setlocale(LC_ALL, "");
    Text MyText;
    wprintf(L"%s\n", "Введите текст(для окончания ввода нажмите Enter)");
    MyText=get_Text();
    MyText=DoSentencesUnique(MyText);
    return (Menu(MyText));
}

int Menu(Text MyText)
{
    int n=3;
    while (1) {
        wprintf(L"Введите число n, в зависимости от которого будут выполнены различные действия: \n 0) Будет произведен выход из программы.\n 1) Будет посчитано и выведено в минутах количество секунд встречающихся в тексте.\n 2) Предложения будут отсортированы по увеличению сумме кодов символов первого слова в предложении.\n 3) Все символы ‘%%’, ‘#’, ‘@’ будут заменены на “<percent>”, “<решетка>”, “(at)” соответственно.\n 4) Все предложения, которые заканчиваются на слово с тремя согласными подряд будут удалены.\n 5) Будет произведен вывод текста на консоль. \n");
        wprintf(L"Введите число n:");
        wscanf(L"%d",&n);
        switch (n) {
            case 0:
                for (int i = 0; i < MyText.text_size; i++) {
                    free(MyText.doc[i].sent);
                }
                free(MyText.doc);
                return 0;
            case 1:
                time(MyText);
                wprintf(L"\n");
                break;
            case 2:
                MyText = UpSort(MyText);
                break;
            case 3:
                MyText = ChangeSpecSym(MyText);
                break;
            case 4:
                MyText = Delete_3_consonant_in_a_row(MyText);
                break;
            case 5:
                text_output(MyText);
                break;
            default:
                wprintf(L"Вы ввели неправильное значение! Пожалуйста, выберите одну из предложенных опций:\n");
                break;
        }
    }
}
