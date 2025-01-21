#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>


#define MAX_SIZE_STRING 90
#define MAX_SIZE_MATRIX 100
#define MAX_SIZE_INPUT 1000

size_t replaceSubstr(const char *srcString, char *dstString, const char *oldSubString, const char *newSubString);

int glasnyChar(char n);

int countZapToString(char *String);

int DeleteDoubleString(char** Array,int maxCount);

int DeleteSubStringRobin(char** Array,int maxCount);

int SortArray(char** Array,int maxCount);

int DeleteSum13(char** Array,int maxCount);

int PrintString(char** Array,int maxCount);



void delete(char *string);

int main() {

    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    //setlocale(LC_CTYPE, "rus");
    setlocale(LC_ALL, "Rus");

//    FILE *fileInput, *fileOutput;
    // объявляем нашу массив как указатель на char и выделяем необходимую память для нее
    char *iputString = (char*)malloc(MAX_SIZE_INPUT * sizeof(char*)), subArray[MAX_SIZE_STRING], ** stringArray = (char**)malloc(MAX_SIZE_MATRIX * sizeof(char*));

    int i=0, count=0, numberZadanie = 0,sizeArray = 0;


    if ( stringArray == NULL ) {
        printf("Не создан массив stringArray \n");
        return -1;
    }


    printf( "Введите данные для обработки : " );


    while ((subArray[i] = getchar()) != '\n') {

        if (subArray[i] == '.') { //если обнаружили точку это конец строки то записываем строку предложения в строку массива

            subArray[i] = '\0';

            stringArray[count] = (char*)malloc(MAX_SIZE_MATRIX * sizeof(char));

            strcpy(stringArray[count], subArray); //  копируем данные (строку) из файла в массив

            count++;
            i = 0;
        }
        else {
            i++;

        }
    }
    //fclose(fileInput);

    //Удаляем дубликаты строк в массиве
    count =  DeleteDoubleString(stringArray,count - 1);

    if (count <0)
        printf("Массив не создан после сжатия \n");

        // Выполнения задания

    printf( "Выберите одно из сдедующих заданий \n" );
    printf( "1. Заменить в тексте подстроку \"Robin\" на \"I am Bathman\" \n" );
    printf( "2. Отсортировать предложения по количеству запятых \n" );
    printf( "3. Удалить все предложения в которых сумма цифр равняется 13\n" );
    printf( "4. Вывести все предложения в которых первое слово начинается с гласной буквы или цифры \n" );
    printf( "5. Выход . \n" );
    printf( "Ваш выбор: " );

    numberZadanie = (int)getchar();
    switch ( numberZadanie ) {
        case '1':
            printf("Выполняем задание 1\n");
            count = DeleteSubStringRobin(stringArray,count);
            break;
        case '2':
            printf("Выполняем задание 2\n");
            count =  SortArray(stringArray,count);
            break;
        case '3':
            printf("Выполняем задание 3\n");
            count =  DeleteSum13(stringArray,count);
            break;
        case '4':
            printf("Выполняем задание 4\n");
            count = PrintString(stringArray,count);
            break;
        case '5':
            printf("Выход \n");
            break;
        default:
            printf( "Неправильный ввод номера задания.\n" );
    }

    //count = result- 1;
// Выводим данные на экран
    if (numberZadanie == '1' || numberZadanie == '2' || numberZadanie == '3'  ){
        printf("\nРезультат:\n");
     for (int i = 0; i < count; i++) {
        printf("%s.\n", stringArray[i]);
     }
    }

    // освобождаем память
    for (int i = 0; i < count; ++i) { free(stringArray[i]); } free(stringArray);
    free(iputString);
    return 0;
}

int DeleteDoubleString(char** Array,int maxCount) //Удаление дублированных строк
{

    int duble_string = 0;


    for (int i = 0; i < maxCount; i++) {

        for (int j = 0; j < maxCount; j++) { //перебираем элементы массива в поисках дублей

            if (i != j){ // это не одна строка
                if (strlen(Array[i]) == strlen(Array[j])){ // сравниваем длинны строк
                    // если длинны строк совпали
                    if (strcasecmp(Array[i], Array[j]) == 0) { // сравниваем содержание строки без регистра

                        //Цикл удаления дублированной строки перещемением последующих строк на строку вверх
                        for (int q = j; q < maxCount; q++) {
                           strcpy( Array[q] , Array[q+1]);
                        }
                        --maxCount;

                    }
                }
           }
        }
    }


   // пересоздаем массив и копируем данные
    char** new_stringArray = (char**)realloc(Array, (maxCount+1) * sizeof(char*));

    if ( new_stringArray != NULL ) {
        Array = new_stringArray;

        return maxCount;

    } else {
        printf("Не создан массив new_stringArray \n");
        return -1 ;
     }

}

int DeleteSubStringRobin(char** Array,int maxCount) //Удаление подстроку Robin
{
    int StartNumSubstr = 0;
    size_t sizeString;
    char *findSubtr,*OldSubString =  "Robin",*NewSubString = "I am Batman",*Newstring = (char*)malloc(StartNumSubstr * sizeof(char));

    for (int i = 0; i <= maxCount ; i++) {

        // заменяем Robin в строке
        sizeString = replaceSubstr(Array[i],Newstring, OldSubString, NewSubString);


        if ( strcasecmp(Array[i],Newstring) != 0){
             strcpy(Array[i], Newstring); // заменяем в массиве данные

        }
    }
}

int SortArray(char** Array,int maxCount) //Сотрировка массива
{
    char * Temp_String;
    // Перебираем каждый элемент массива (кроме последнего, он уже будет отсортирован к тому времени, когда мы до него доберемся)
    for (int startIndex = 0; startIndex <= maxCount ; ++startIndex) {
        // В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
        // Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
        int smallestIndex = startIndex;

        // Затем ищем элемент поменьше в остальной части массива
        for (int currentIndex = startIndex + 1; currentIndex <= maxCount; ++currentIndex) {
            // Если мы нашли элемент, который меньше нашего наименьшего элемента,
            if (countZapToString(Array[currentIndex]) < countZapToString(Array[smallestIndex]))  // сравниваем по количеству запятых в строке
                // то запоминаем его
                smallestIndex = currentIndex;
        }

        // smallestIndex теперь наименьший элемент.
        // Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили

        Temp_String = Array[startIndex];
        Array[startIndex] = Array[smallestIndex];
        Array[smallestIndex] = Temp_String;
        //std::swap(array[startIndex], rray[smallestIndex]);
    }

}

int DeleteSum13(char** Array,int maxCount) //Удалить все предложения где сумма цифр равна 13
{
    int NumberTemp = 0,Razrayd = 0;

    int sum = 0;
    for (int i = 0; i <= maxCount; i++) {

        // считаем сумму цифр в строке массива

        for (int j = 0; j < strlen(Array[i]); j++)
        {
            if (('1' <= Array[i][j]) && (Array[i][j] <= '9')) { // определяем что символ это цифра между 1 и 9
                NumberTemp = atoi(&Array[i][j]);
                sum = sum + NumberTemp;
                // определяем разрядности числа из строки . На сколько разрядов число больше 10 изза особенности реализации функции atoi()
                while(NumberTemp>10){
                    NumberTemp = NumberTemp / 10;
                    ++j; //Двигаем указатель по строке
                }

            }
        }
        if ( sum == 13){ // удаляем  в массиве строки с суммой цифр равной 13
            //Цикл удаления  строки перещемением последующих строк на строку вверх
            for (int q = i; q < maxCount; q++)
                strcpy( Array[q] , Array[q+1]);
           //--i;        // итератор уменьшаем так как строку удалили
           --maxCount; // уменьшаем размер массина на одну строку
        }
        sum = 0; // обнуляем для следующей строки
    }

    // пересоздаем массив и копируем данные
    char** new_stringArray = (char**)realloc(Array, (maxCount+1) * sizeof(char*));

    if ( new_stringArray != NULL ) {
        Array = new_stringArray;

        return maxCount + 1;

    } else {
        printf("Не создан массив new_stringArray \n");
        return -1 ;
    }

}

int PrintString(char** Array,int maxCount) //Вывести все предложения  где .....
{
    printf("\nРезультат:\n");
    for (int i = 0; i <= maxCount; i++) {

        for (int j = 0; j < strlen(Array[i]); j++) { // перебираем строку

          if (Array[i][j] != ' ' ) {
              if (('0' <= Array[i][j]) && (Array[i][j] <= '9') || glasnyChar(Array[i][j])) { // определяем что Первый символ это цифра  1 и 9 или гласная
                  printf("%s \n", Array[i]);
              }
              break;
          }
         }
        }

}

int countZapToString(char *String)
{
   int count = 0;
    for (int i = 0; String[i] != '\0'; i++){
        if (String[i] == ',') // ищем символ запятая
            count++;
    }
    return count;
}

size_t replaceSubstr(const char *srcString, char *dstString, const char *oldSubString, const char *newSubString)
{
    size_t l_old = strlen(oldSubString), l_new = strlen(newSubString);
    size_t dst_length = 0;

    const char *src_current = srcString;
    do
    {
        const char *src_next = strstr(src_current, oldSubString);
        if (src_next == NULL)
        {
            if (dstString != NULL)
                strcpy(dstString + dst_length, src_current);

            dst_length += strlen(src_current);

            break;
        }

        size_t n = src_next - src_current;

        if (dstString != NULL)
            memcpy(dstString + dst_length, src_current, n);

        dst_length += n;

        if (dstString != NULL)
            memcpy(dstString + dst_length, newSubString, l_new);

        dst_length += l_new;

        src_current = src_next + l_old;
    } while (1);

    return dst_length;
}

int glasnyChar(char n)
{
    int k = 0;
    char mas[12] = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'u', 'Y'};
    for (int i = 0; i < 12; i++)
    {
        if (n == mas[i])
            k++;
    }
    if (k == 1)
        return 1;
    else
        return 0;
}
