#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

void print_path(char* path, FILE* file, char* word, int index) {
    DIR *dir = opendir(path);
    int len = (int)strlen(path);
    if (dir) {
        struct dirent *de = readdir(dir);
        while (de != NULL) {
            if(de->d_name[0] == '.'){
                de = readdir(dir);
                continue;
            }
            strcat(path,"/");
            strcat(path,de->d_name);
            if (de->d_type == 8) {
                if(de->d_name[0] == word[index] && de->d_name[1] == '.') {
                    fprintf(file, "%s\n", path);
                }
            }
            else if(de->d_type == 4){
                print_path(path, file, word, index);
            }
            path[len] = '\0';
            de = readdir(dir);
        }
    }
    closedir(dir);
}

int main() {
    char path[150] = "./tmp";
    int index;
    char word[100];
    fgets(word, 100, stdin);
    FILE *file = fopen("result.txt", "w");
    for (index = 0; index < strlen(word); index++) {
        print_path(path, file, word, index);
    }
    fclose(file);
    return 0;
}
