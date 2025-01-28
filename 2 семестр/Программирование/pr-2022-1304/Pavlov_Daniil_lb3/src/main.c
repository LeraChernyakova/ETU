 #include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>


char* get_input_string(){
    char* result = NULL;
    result = malloc(sizeof(char));

    int i = 0;
    do{
        result = realloc(result, sizeof(char)*(i+1));
        scanf("%c", &result[i]);
        if (result[i] == '\n'){
            result[i] = '\0';
            break;
        }
        i++;
    }while (1);

    return result;
}

_Bool is_filename_correct(const char* filename){
    if (strlen(filename) == 5){
        if ((filename[1] == '.') && (filename[2] == 't') && (filename[3] == 'x') && (filename[4] == 't')){
            return true;
        }
    }
    return false;

}

void list_dir(const char *dirPath, char symbol, FILE* res, _Bool flag){
    if (flag == true) {
        DIR *dir = opendir(dirPath);
        if (dir) {
            struct dirent *de = readdir(dir);


            while (de) {
                if (strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
                    char path[200];

                    path[0] = '\0';
                    strcat(path, dirPath);
                    strcat(path, de->d_name);

                    if (strstr(de->d_name, ".txt") != NULL && is_filename_correct(de->d_name) == true &&
                        (de->d_name)[0] == symbol) {
                        flag = false;
                        fprintf(res, "%s\n", path);
                        return;
                    } else {
                        //printf("%s\n", s);
                    }
                    if (opendir(path) == NULL) {

                    } else {
                        strcat(path, "/");
                        //strcat(path, "\\");
                        list_dir(path, symbol, res, flag);
                    }
                }
                de = readdir(dir);
            }
        }
        closedir(dir);
    }else if(flag == false){
        return;
    }
}

int main() {
    char* string = NULL;
    FILE* result;
    result = fopen("result.txt", "w");

    //char* head_path = "/Users/pavlov/Desktop/hello_world_test/";
    //char* head_path = "\\tmp\\";
    char* head_path = "./tmp/";
    string = get_input_string();
    int i;
    _Bool flag = true;
    for (i = 0; i < strlen(string); i++) {
        list_dir(head_path,string[i], result, flag);
        flag = true;
    }
    fclose(result);
    free(string);
    return 0;
}

