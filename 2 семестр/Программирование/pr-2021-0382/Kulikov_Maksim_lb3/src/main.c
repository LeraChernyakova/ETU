#define _GNU_SOURCE
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>


#define BUF 5000


int cmp(const void *a, const void *b) {
    const char *aa = *(char **) a;
    const char *bb = *(char **) b;
    long int a1 = atol(aa);
    long int b1 = atol(bb);
    if (a1 > b1)
        return 1;
    if (a1 < b1)
        return -1;
    return 0;
}

char **get_text(const char *path, char **text, int *counter) {
    char s[100];

    FILE *f = fopen(path, "r");
    if (!f) {
        return text;
    }

    while (fgets(s, 100, f)) {
        strcat(text[*counter], s);
    }

    fclose(f);
    return text;
}

char **listDir(const char *path, char **text, int *counter) {
    char next[256] = {0};
    strcpy(next, path);
    strcat(next, "/");

    DIR *dir = opendir(path);
    if (!dir) {
        return text;
    }
    struct dirent *de = readdir(dir);

    while (de) {
        if (de->d_type == DT_REG) {
            int len = strlen(next);
            strcat(next, de->d_name);
            get_text(next, text, counter);
            *counter = *counter + 1;
            next[len] = '\0';
        }

        if ((de->d_type == DT_DIR) && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            int len = strlen(next);
            strcat(next, de->d_name);
            listDir(next, text, counter);
            next[len] = '\0';
        }
        de = readdir(dir);
    }

    closedir(dir);
    return text;
}

int main() {
    int counter = 0;
    char **text = calloc(BUF, sizeof(char *));
    for (int i = 0; i < BUF; i++) {
        text[i] = calloc(BUF, sizeof(char));
    }

    text = listDir("root", text, &counter);
    qsort(text, counter, sizeof(char *), cmp);

    FILE *f = fopen("result.txt", "w");
    for (int i = 0; i < counter; i++) {
        if (text[i][0] != '\0')
            fprintf(f, "%s\n", text[i]);
    }
    fclose(f);

    for (int i = 0; i < BUF; i++) {
        free(text[i]);
    }
    free(text);
    return 0;
}

