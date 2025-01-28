#include <stdio.h>
#include <dirent.h>
#include <string.h>

long long mul(char *curPath);

long long add(char *curPath) {
    FILE *fptr;
    DIR *dir = opendir(curPath);
    long long res = 0, n;
    char c;
    if (dir) {
        struct dirent *de = readdir(dir);
        while (de) {
            if (de->d_name[0] == '.') {
                de = readdir(dir);
                continue;
            }
            if (de->d_type == DT_DIR && strcmp(de->d_name, "add") == 0) {
                strcat(curPath, "/add");
                res = res + add(curPath);
                curPath[strlen(curPath) - 4] = '\0';
            } else if (de->d_type == DT_DIR && strcmp(de->d_name, "mul") == 0) {
                strcat(curPath, "/mul");
                res = res + mul(curPath);
                curPath[strlen(curPath) - 4] = '\0';
            } else { // text file
                strcat(curPath, "/");
                strcat(curPath, de->d_name);
                fptr = fopen(curPath, "r");
                fscanf(fptr, "%lld", &n);
                c = fgetc(fptr);
                res = res + n;
                while (c != EOF && c != '\n' && fscanf(fptr, "%lld", &n) != EOF) {
                    c = fgetc(fptr);
                    res = res + n;
                }
                fclose(fptr);
                curPath[strlen(curPath) - strlen(de->d_name) - 1] = '\0';
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
    return res;
}

long long mul(char *curPath) {
    FILE *fptr;
    DIR *dir = opendir(curPath);
    long long res = 0, n, flag = 0;
    char c, c1;
    if (dir) {
        struct dirent *de = readdir(dir);
        while (de) {
            if (de->d_name[0] == '.') {
                de = readdir(dir);
                continue;
            }
            if (de->d_type == DT_DIR && strcmp(de->d_name, "add") == 0) {
                strcat(curPath, "/add");
                res = res * add(curPath);
                curPath[strlen(curPath) - 4] = '\0';
            } else if (de->d_type == DT_DIR && strcmp(de->d_name, "mul") == 0) {
                strcat(curPath, "/mul");
                res = res * mul(curPath);
                curPath[strlen(curPath) - 4] = '\0';
            } else { // text file
                if (flag == 0) {
                    flag = 1;
                    res = 1;
                }
                strcat(curPath, "/");
                strcat(curPath, de->d_name);
                fptr = fopen(curPath, "r");
                fscanf(fptr, "%lld", &n);
                c = fgetc(fptr);
                res = res * n;
                while (c != EOF && c != '\n' && fscanf(fptr, "%lld", &n) != EOF) {
                    c = fgetc(fptr);
                    res = res * n;
                }
                fclose(fptr);
                curPath[strlen(curPath) - strlen(de->d_name) - 1] = '\0';
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
    return res;
}

int main() {
    char cwd[10000];
    strcpy(cwd, ".");
    strcat(cwd, "/result.txt");
    FILE *fres = fopen(cwd, "w");
    cwd[strlen(cwd) - 11] = '\0';
    strcat(cwd, "/tmp");
    fprintf(fres, "%lld", add(cwd));
    return 0;
}
