#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
typedef struct MusicalComposition
{
    char name[80];
    char author[80];
    int year;
    struct MusicalComposition *next;
    struct MusicalComposition *prev;
} MusicalComposition;
// Описание структуры MusicalComposition


// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
    MusicalComposition *cur = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    strcpy(cur->name, name);
    strcpy(cur->author, autor);
    cur->year = year;
    cur->next = cur->prev = NULL;
    return cur;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    int i; MusicalComposition* present; MusicalComposition* head; MusicalComposition* past;
    head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    past = head;
    for (i = 1; i<n; i++)
    {
        present = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        if (i == n-1) present->next=NULL;
        past->next = present;
        present->prev = past;
        past = present;
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    element->next=NULL;
    while(head->next!=NULL) head = head->next;
    head->next=element;
    element->prev=head;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    while (head)
    {
        if (!strcmp(head->name, name_for_remove))
        {head->next->prev = head->prev; head->prev->next = head->next;
        }
        head = head->next;
    }
}

int count(MusicalComposition* head) {
    int countt=1;
    while (head->next != NULL) {
        countt++;
        head = head->next;
    }
    return countt;
}

void print_names(MusicalComposition* head){
    MusicalComposition *present = head;
    while (present != NULL)
    {   printf("%s\n", present->name);
        present = present->next;
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
