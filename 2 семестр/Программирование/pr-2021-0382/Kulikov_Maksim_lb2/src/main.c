#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct MusicalComposition {
    char *name;
    char *author;
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *before;
};

typedef struct MusicalComposition MusicalComposition;

MusicalComposition *createMusicalComposition(char *name, char *author, int year) {
    MusicalComposition *elem = malloc(sizeof(struct MusicalComposition));
    elem->name = name;
    elem->author = author;
    elem->year = year;
    elem->before = NULL;
    elem->next = NULL;

    return elem;

}

MusicalComposition *createMusicalCompositionList(char **array_names, char **array_authors, int *array_years, int n) {
    MusicalComposition *head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition *before = head;
    MusicalComposition *cur = NULL;
    for (int i = 1; i < n; i++) {
        cur = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        before->next = cur;
        cur->before = before;
        before = cur;
    }
    cur->next = NULL;

    return head;

}

void push(MusicalComposition *head, MusicalComposition *element) {
    MusicalComposition *cur = head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = element;
    element->before = cur;
    element->next = NULL;

}

void removeEl(MusicalComposition *head, char *name_for_remove) {
    MusicalComposition *cur = head;
    MusicalComposition *tmp = NULL;
    while (cur != NULL) {
        if (!(strcmp(cur->name, name_for_remove))) {
            if (cur->before == NULL) {
                tmp = cur;
                cur->before = cur->next->before;
                cur = cur->next;
                free(tmp);
            } else {
                if (cur->next == NULL) {
                    tmp = cur;
                    cur->before->next = NULL;
                    cur = cur->before;
                    free(tmp);
                } else {
                    tmp = cur;
                    cur->next->before = cur->before;
                    cur->before->next = cur->next;
                    cur = cur->next;
                    free(tmp);

                }
            }
        }
        else{
            cur = cur -> next;
        }
    }


}

int count(MusicalComposition *head) {
    int n = 1;
    MusicalComposition *cur = head;
    while(cur->next != NULL){
        cur = cur-> next;
        n+=1;
    }

    return n;
}

void print_names(MusicalComposition *head) {
    MusicalComposition *cur = head;
    while (cur != NULL) {
        printf("%s\n", cur->name);
        cur = cur->next;
    }
}


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

    return 0;

}
