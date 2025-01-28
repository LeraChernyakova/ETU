#include <stdio.h>
#include <dirent.h>
#include <string.h>

long long mul(char *actualPath);

long long add(char *actualPath){
    FILE *f;
    DIR *d = opendir(actualPath);
    long long result = 0, n;
    char c;
    if (d) {
        struct dirent *der = readdir(d);
        while (der) {
            if (der->d_name[0] == '.'){
                der = readdir(d);
                continue;
            }
            if (der->d_type == DT_DIR && strcmp(der->d_name, "add") == 0) {
                strcat(actualPath, "/add");
                result += add(actualPath);
                actualPath[strlen(actualPath) - 4] = '\0';
            }
            else if (der->d_type == DT_DIR && strcmp(der->d_name, "mul") == 0) {
                strcat(actualPath, "/mul");
                result += mul(actualPath);
                actualPath[strlen(actualPath) - 4] = '\0';
            }
            else {
                strcat(actualPath, "/");
                strcat(actualPath, der->d_name);
                f = fopen(actualPath, "r");
                fscanf(f, "%lld", &n);
                c = fgetc(f);
                result += n;
                while (c != EOF && c != '\n' && fscanf(f, "%lld", &n) != EOF) {
                    c = fgetc(f);
                    result += n;
                }
                fclose(f);
                actualPath[strlen(actualPath) - strlen(der->d_name) - 1] = '\0';
            }
            der = readdir(d);
        }
    }
    closedir(d);
    return result;
}

long long mul(char *actualPath) {
    FILE *f;
    DIR *d = opendir(actualPath);
    long long result = 0, n, flag = 0;
    char c, c1;
    if (d) {
        struct dirent *der = readdir(d);
        while (der) {
            if (der->d_name[0] == '.') {
                der = readdir(d);
                continue;
            }
            if (der->d_type == DT_DIR && strcmp(der->d_name, "add") == 0) {
                strcat(actualPath, "/add");
                result *= add(actualPath);
                actualPath[strlen(actualPath) - 4] = '\0';
            }
            else if (der->d_type == DT_DIR && strcmp(der->d_name, "mul") == 0) {
                strcat(actualPath, "/mul");
                result *= mul(actualPath);
                actualPath[strlen(actualPath) - 4] = '\0';
            }
            else {
                if (flag == 0) {
                    flag = 1;
                    result = 1;
                }
                strcat(actualPath, "/");
                strcat(actualPath, der->d_name);
                f = fopen(actualPath, "r");
                fscanf(f, "%lld", &n);
                c = fgetc(f);
                result *= n;
                while (c != EOF && c != '\n' && fscanf(f, "%lld", &n) != EOF) {
                    c = fgetc(f);
                    result *= n;
                }
                fclose(f);
                actualPath[strlen(actualPath) - strlen(der->d_name) - 1] = '\0';
            }
            der = readdir(d);
        }
    }
    closedir(d);
    return result;
}

int main() {
    char str[10000];
    strcpy(str, ".");
    strcat(str, "/result.txt");
    FILE *fresult = fopen(str, "w");
    str[strlen(str) - 11] = '\0';
    strcat(str, "/tmp");
    fprintf(fresult, "%lld", add(str));
    return 0;
}


