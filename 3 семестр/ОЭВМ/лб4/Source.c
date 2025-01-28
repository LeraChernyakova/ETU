#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <Windows.h>



#define INP_STR_SIZE 100

char input_string[INP_STR_SIZE];     //строка для входных данных
char output_string[INP_STR_SIZE * 4];//строка для выходных данных
char map[][2];                       //объявление массива соответствий (определение в конце кода)

void printGreeting();

int main() {
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251); 
    printGreeting();
    fgets(input_string, INP_STR_SIZE, stdin);
    __asm {
        push ds
        pop es
        mov esi, offset input_string
        mov edi, offset output_string
        head :
            lodsb                    //считываем в al символ
            cmp al, 'Ё'
            je jumpIfYoCharCapital   //проверяем крайние случаи (Ё - "не по порядку" в таблице)
            cmp al, 'ё'
            je jumpIfYoChar       
            cmp al, 'Щ'
            je jumpIfShchCharCapital //проверяем крайние случаи (Щ - единственная занимает 4 символа после транслитерации)
            cmp al, 'щ'
            je jumpIfShchChar
            cmp al, 192
            jge compareForRusChar
            stosb                   //иначе просто записывается в output строку
            jmp final
            compareForRusChar:      //значение между 192 и 255 => символ русский и идёт на обработку
            cmp al, 255
            jle rusChar
            stosb                   //иначе просто записывается в output строку
            jmp final
            rusChar :
            lea ebx, map            //загружаем массив соотв. для работа с xlatb
            sub al, 192             //вычитаем из считанного lotsb символа 192, (т.е. А = 0....Я=31....а=32...я=63) 
            sal al, 1               //умножаем индекс на 2 в силу формата массива соответствий
            mov ah, al
            add ah, 1               //запоминаем следующий символ
            xlatb
            cmp al, ' '             //пропускаем пробелы
            je jumpIfSpace
            stosb                   //считываем два символа в output
      //      mov al, ah
            xlatb
            cmp al, ' '             //пропускаем пробелы
            je jumpIfSpace
            stosb
            jmp final
            jumpIfShchCharCapital:  // обрабатываем крайние случаи вручную
                mov al, 'S'
                stosb
                mov al, 'h'
                stosb
                mov al, 'c'
                stosb
                mov al, 'h'
                stosb
                jmp final
            jumpIfYoCharCapital:    // обрабатываем крайние случаи вручную
                mov al, 'Y'
                stosb
                mov al, 'o'
                stosb
                jmp final
                jumpIfYoChar :
                mov al, 'y'
                stosb
                mov al, 'o'
                stosb
                jmp final
            jumpIfShchChar :        // обрабатываем крайние случаи вручную
                mov al, 's'
                stosb
                mov al, 'h'
                stosb
                mov al, 'c'
                stosb
                mov al, 'h'
                stosb
                jmp final
            jumpIfSpace:            //пропускаем пробелы при обработке русских символов
            final:
                mov ecx, '\0'       //проверяем на конец строки (заканчиваем, если дошли до \0)
                cmp ecx, [esi]
                je ENDPROG
                jmp head
        ENDPROG:
    };
    output_string[strlen(output_string)] = '\0';
    printf("%s", output_string);
    

    FILE* fptr;
    fopen_s(&fptr,"processed_str.txt", "w");
    if (fptr != NULL)
    {
        fprintf(fptr, "%s", output_string);
    }
    puts("Нажмите ENTER для завершения программы");
    getchar();
    return 0;
}

void printGreeting()
{
    printf("Кривоченко Дмитрий | группа 1304 | Вариант - 13\n");
    printf("Преобразование введенных во входной строке русских букв в латинские в\n");
    printf("соответствие с правилами транслитерации, остальные символы входной строки\n");
    printf("передаются в выходную строку непосредственно.\n");
    printf("Введите строку для обработки:\n");
}

char map[][2] = { 'A',' ','B',' ', 'V',' ', 'G',' ', 'D',' ', 'Y', 'e', 'Z','h','Z',' ',
'I',' ','Y',' ', 'K',' ', 'L',' ','M',' ','N',' ', 'O',' ', 'P',' ', 'R',' ', 'S',' ', 'T',' ',
'U',' ', 'F',' ', 'K','h', 'T','s', 'C','h', 'S','h', ' ',' ', (char)34, ' ', 'y',' ', (char)39,' ',
'E',' ', 'Y','u', 'Y','a',
'a',' ','b',' ', 'v',' ', 'g',' ', 'd',' ', 'y', 'e', 'z','h','z',' ',
'i',' ','y',' ', 'k',' ', 'l',' ','m',' ','n',' ', 'o',' ', 'p',' ', 'r',' ', 's',' ', 't',' ',
'u',' ', 'f',' ', 'k','h', 't','s', 'c','h', 's','h', ' ',' ', (char)34, ' ', 'y',' ', (char)39,' ',
'e',' ', 'y','u', 'y','a' };