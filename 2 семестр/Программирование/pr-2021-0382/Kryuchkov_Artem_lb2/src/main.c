#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition MusicalComposition;
// Описание структуры MusicalComposition

struct MusicalComposition {
    char *name;
    char *author;
    int year;
    MusicalComposition *PreviousComposition;
    MusicalComposition *NextComposition;
};

// Создание структуры MusicalComposition
MusicalComposition *createMusicalComposition(char *name, char *author, int year);

// Функции для работы со списком MusicalComposition.

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n);

void push(MusicalComposition *head, MusicalComposition *element);

void removeEl(MusicalComposition *head, char *name_for_remove);

int count(MusicalComposition *head);

void print_names(MusicalComposition *head);

int main() {
    int length;
    scanf("%d\n", &length);

    char **names = (char **) malloc(sizeof(char *) * length);
    char **authors = (char **) malloc(sizeof(char *) * length);
    int *years = (int *) malloc(sizeof(int) * length);

    for (int i = 0; i < length; i++) {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name, "\n")) = 0;
        (*strstr(author, "\n")) = 0;

        names[i] = (char *) malloc(sizeof(char *) * (strlen(name) + 1));
        authors[i] = (char *) malloc(sizeof(char *) * (strlen(author) + 1));

        strcpy(names[i], name);
        strcpy(authors[i], author);
    }
    MusicalComposition *head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push, "\n")) = 0;
    (*strstr(author_for_push, "\n")) = 0;

    MusicalComposition *element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove, "\n")) = 0;

    printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(head, name_for_remove);
    print_names(head);

    k = count(head);
    printf("%d\n", k);

    for (int i = 0; i < length; i++) {
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);
}

MusicalComposition *createMusicalComposition(char *name, char *author, int year) {
    MusicalComposition *composition = (MusicalComposition *) malloc(sizeof(MusicalComposition));
    composition->name = (char *) (malloc(sizeof(char) * 81));
    composition->author = (char *) (malloc(sizeof(char) * 81));
    strncpy(composition->name, name, 80);
    strncpy(composition->author, author, 80);
    composition->year = year;
    composition->NextComposition = NULL;
    return composition;
}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n) {
    if (n == 0)
        return NULL;
    MusicalComposition *HeadComposition = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);

    // Head initialization
    HeadComposition->NextComposition = NULL;
    HeadComposition->PreviousComposition = NULL;

    if (n == 1)
        return HeadComposition;
    MusicalComposition *tempComposition = createMusicalComposition(array_names[1], array_authors[1], array_years[1]);;
    HeadComposition->NextComposition = tempComposition;
    tempComposition->PreviousComposition = HeadComposition;

    for (int i = 2; i < n; ++i) {
        tempComposition->NextComposition = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        tempComposition->NextComposition->PreviousComposition = tempComposition;
        tempComposition = tempComposition->NextComposition;
    }

    return HeadComposition;
}

void push(MusicalComposition *head, MusicalComposition *element) {
    while (head->NextComposition != NULL) {
        head = head->NextComposition;
    }
    element->PreviousComposition = head;
    head->NextComposition = element;
}

void removeEl(MusicalComposition *head, char *name_for_remove) {
    while (head->NextComposition != NULL) {
        if (strcmp(head->name, name_for_remove) == 0) {
            if (head->NextComposition == NULL) {
                head->PreviousComposition->NextComposition = NULL;
            } else if (head->PreviousComposition == NULL) {
                head->NextComposition->PreviousComposition = NULL;
            } else {
                head->PreviousComposition->NextComposition = head->NextComposition;
                head->NextComposition->PreviousComposition = head->PreviousComposition;
            }
            free(head->author);
            free(head->name);
            free(head);
            return;
        }
        head = head->NextComposition;
    }
}

int count(MusicalComposition *head) {
    int res = 1;
    while (head->NextComposition != NULL) {
        head = head->NextComposition;
        res++;
    }
    return res;
}

void print_names(MusicalComposition *head) {
    while (head->NextComposition != NULL) {
        printf("%s\n", head->name);
        head = head->NextComposition;
    }
    printf("%s\n", head->name);
}
