#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Описание структуры MusicalComposition

struct MusicalComposition{
    char name[81];
    char author[81];
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
};

typedef struct MusicalComposition MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* musical_composition;
    musical_composition = malloc(sizeof(MusicalComposition));
    musical_composition->prev = NULL;
    musical_composition->next = NULL;
    strcpy(musical_composition->name, name);
    strcpy(musical_composition->author, author);
    musical_composition->year = year;
    return musical_composition;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = (struct MusicalComposition*)malloc(sizeof(struct MusicalComposition));
    MusicalComposition* cur = head;
    MusicalComposition* prev = NULL;
    for(int i = 0; i < n; i++){
        cur->prev = prev;
        strcpy(cur->name, array_names[i]);
        strcpy(cur->author, array_authors[i]);
        cur->year = array_years[i];
        prev = cur;
        if (i < n - 1){
            cur = (struct MusicalComposition*)malloc(sizeof(struct MusicalComposition));
            prev->next = cur;
        }
    }
    prev->next = NULL;
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* cur = head;
    while(cur->next != NULL)
        cur = cur->next;
    cur->next = element;
    element->prev = cur;
    element->next = NULL;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    struct MusicalComposition* cur = head;
    while(strcmp(cur->name, name_for_remove))
        cur = cur->next;
    if (cur->prev != NULL)
        cur->prev->next = cur->next;
    if(cur->next != NULL)
        cur->next->prev = cur->prev;
    free(cur);
}

int count(MusicalComposition* head){
    MusicalComposition* cur = head;
    int n = 1;
    while(cur->next != NULL){
        n++;
        cur = cur->next;
    }
    return n;
}

void print_names(MusicalComposition* head){
    MusicalComposition* cur = head;
    while(cur != NULL){
        printf("%s\n", cur->name);
        cur = cur->next;
    }
}


int main(){
    int length;
    scanf("%d\n", &length);

    char** names = (char**)malloc(sizeof(char*)*length);
    char** authors = (char**)malloc(sizeof(char*)*length);
    int* years = (int*)malloc(sizeof(int)*length);

    for (int i=0;i<length;i++)
    {
        char name[80];
        char author[80];

        fgets(name, 80, stdin);
        fgets(author, 80, stdin);
        fscanf(stdin, "%d\n", &years[i]);

        (*strstr(name,"\n"))=0;
        (*strstr(author,"\n"))=0;

        names[i] = (char*)malloc(sizeof(char*) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char*) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    MusicalComposition* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

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

    for (int i=0;i<length;i++){
        free(names[i]);
        free(authors[i]);
    }
    free(names);
    free(authors);
    free(years);

    return 0;
}