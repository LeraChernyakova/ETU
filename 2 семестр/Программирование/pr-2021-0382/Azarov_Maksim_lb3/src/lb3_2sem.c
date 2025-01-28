#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>


#define START_DIR  "./labyrinth"
#define RESULT_FILE "./result.txt"
#define START_FILE "file.txt"
#define MAX_LEN_PATH 100
#define MAX_LEN_F_NAME 15
#define INIT_SIZE_LAB 50
#define INIT_SIZE_ANS 50



struct labyrinth {
    char** path; //путь к файлу
    char** f_name; //имя файла
    int n; // количество файлов
    int max_n; //текущее максимальное количество файлов
};
typedef struct labyrinth labyrinth;

struct Stack {
    char** arr;
    int n;
    int max_n;
};
typedef struct Stack Stack;

char* my_strcat(char* s12 , char* s1, char* s2) {

    strcpy(s12, s1);
    strcat(s12, s2);
    return s12;
}


void get_labyrinth(char* old_path, labyrinth* lab) { //Опис.: рекурсивно находит все файлы и пути к ним
    DIR* dir = opendir(old_path); //открываем директорию по пути old_path
    char path[100];
    int len;

    strcpy(path, old_path); //копируем old_path в path
    strcat(path, "/");

    if (dir == NULL) { //проверяем успешно ли открыта дир.
        printf("ERROR: dir = NULL");
        return;
    }

    struct dirent* inf_file = readdir(dir); // получаем инф о первом файле в дир.
    while (inf_file) {//пока есть файлы в дир.

        if ( (inf_file->d_type == DT_DIR) && (strcmp(inf_file->d_name, ".")) != 0 //если это папка
            && (strcmp(inf_file->d_name, "..")) != 0 ) {

            len = strlen(path);
            get_labyrinth(strcat(path, inf_file->d_name),lab); //рекурсия: снова вызываем get_labyrinth() для поиска
            path[len] = '\0';                                  // файлов но уже в найденной дир.
        }

        if (inf_file->d_type == DT_REG) {  //если это обычный файл
            if (lab->n == lab->max_n - 1) { //проверяем есть ли в lab место для нового файла
                lab->max_n += 50;
                lab->f_name = realloc(lab->f_name, lab->max_n*sizeof (char*));
                lab->path = realloc(lab->path, lab->max_n*sizeof (char*));
            }

            char* tmp_f_name = malloc(MAX_LEN_F_NAME * sizeof (char)); //
            char* tmp_path = malloc(MAX_LEN_PATH * sizeof (char));

            strcpy(tmp_f_name , inf_file->d_name);
            strcpy(tmp_path, path);

            lab->f_name[lab->n] = tmp_f_name; //сохраняем в структуру lab название найденого файла
            lab->path[lab->n] = tmp_path; //сохраняем в структуру lab путь к найденому файлу
            lab->n ++;

        }

        inf_file = readdir(dir); // получаем инф о cлед. файле в дир.
    }

    closedir(dir); //закрываем дир.
    return;
}



void pop(Stack* ans, char* path) {
    char *tmp = malloc(MAX_LEN_PATH * sizeof (char));
    if (ans->n == ans->max_n - 1) { //пров-ка на наличии свобод. места для доб.
        ans->max_n += 50;
        ans->arr = realloc(ans->arr, ans->max_n*sizeof (char*));
    }

    strcpy(tmp, path);

    ans->arr[ans->n] = tmp;
    ans->n++;

    return;
}

char* push(Stack* ans) {
    if ( ans->n == 0) {
        return NULL;
    }

    ans->n --;
    return  ans->arr[ans->n];
}


int found_minotaur(labyrinth lab,char* f_name, Stack* ans) { //рекурсивно ишет минотавра
    int i;
    char str[50], f_name_next[50];  //стока для чтения файла , вспомогательная строка для удаления "@include "
    char* t;    // вспомогательный указателя для поиска и удаления \n в считанной строке
    char tmp[100];  //вспомогательная строка для конкатенации строк

    for (i = 0; i < lab.n; i++) {   //средивсех найденых файлов в lab
        if (strcmp(lab.f_name[i], f_name) == 0) {   //ищет файл с именем f_name

            //после нахождения файла
            FILE* f = fopen( my_strcat(tmp, lab.path[i], lab.f_name[i]) ,"r");  //открывайм найденный файл для чтения по
                                                                                        // соответствующему пути  в lab
            fgets(str, 50, f); // читаем первую строку в файле
            t = strchr(str, '\n');      //удаляем \n, если он есть
            if ( t != NULL) {
                *t = '\0';
            }

            if (strcmp(str, "Deadlock") == 0) { //если считанная строка "Deadlock"
                fclose(f); //закрываем файл
                return 0;   //и выходим из текущей фун , возращая 0
            }

            if (strcmp(str, "Minotaur") == 0) { //если считанная строка  "Minotaur"
                fclose(f);  //закрываем файл
                pop(ans, my_strcat(tmp, lab.path[i], lab.f_name[i]));   //добавляем в ans путь к текущему файлу
                return 1; //возвращаем 1
            }

            do { //если ничего выше не подощло значит остался только
                 // вариант  ссылкок на другие файлы
                strcpy(f_name_next , str+9);  //удаляем "@include "
                t = strchr(f_name_next, '\n');  //удаляем \n, если он есть
                if ( t != NULL) {
                    *t = '\0';
                }

                if ( found_minotaur(lab, f_name_next, ans) == 1) {  //ищем и читаем новый  файл  найденый в тукущем файле
                                                                    //с помощью found_minotaur()
                                                                    //если фун вернула 1 то значит фай-минотавр был найден
                    fclose(f);//закрываем файл
                    pop(ans, my_strcat(tmp, lab.path[i], lab.f_name[i]));  //добавляем в ans путь к текущему файлу
                    return 1; //возвращаем 1

                }
            } while (fgets(str, 50, f)); //читаем файл пока в нем есть строки

            fclose(f);  //если среди ссылок небыло путя к файлу-минотавр , то закрываем файл
            return 0;   //возвразаем 0

        }
    }
}

void write_answer(Stack* ans){
    char* tmp;
    FILE* f = fopen(RESULT_FILE,"w");

    tmp = push(ans);
    while (tmp){
        fprintf(f,"%s\n", tmp);
        tmp = push(ans);
    }

    fclose(f);

    return;
}

void clear_dynamic_arr(labyrinth* lab,Stack* ans) {
    int i;

    for (i = 0; i < lab->n ; i++){
        free(lab->f_name[i]);
        free(lab->path[i]);
    }
    free(lab->f_name);
    free(lab->path);

    for (i = 0; i < ans->n ; i++) {
        free(ans->arr[i]);
    }
    free(ans->arr);
}





int main() {
    labyrinth lab = {.n = 0, .max_n = INIT_SIZE_LAB};
    Stack answer = {.n = 0, .max_n = INIT_SIZE_ANS};

    answer.arr = malloc(answer.max_n * sizeof (char*));

    lab.f_name = malloc(lab.max_n * sizeof (char*));
    lab.path = malloc(lab.max_n * sizeof (char*));

    get_labyrinth(START_DIR, &lab);
    found_minotaur(lab, START_FILE, &answer);

    write_answer(&answer);

    //незабудь очистить ans и lab!!!
    //незабыл)

    clear_dynamic_arr(&lab, &answer);

    return 0;
}
