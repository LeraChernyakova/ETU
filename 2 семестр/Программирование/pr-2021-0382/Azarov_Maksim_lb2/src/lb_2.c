#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>


// Описание структуры MusicalComposition
struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
};


typedef struct MusicalComposition MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
    MusicalComposition* tmp = (MusicalComposition*)malloc(sizeof(MusicalComposition));

    tmp->name = name;
    tmp->author = autor;
    tmp->year = year;

    return tmp;
}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    if (n==0){return NULL;}

    MusicalComposition* head = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    MusicalComposition* tmp = head;

    head->name = array_names[0];
    head->author = array_authors[0];
    head->year = array_years[0];
    head->prev = NULL;

    for (int i = 1; i < n; i++){
        tmp->next = (MusicalComposition*)malloc(sizeof(MusicalComposition));
        tmp->next->prev = tmp; //указ. на пред. идущий
        tmp = tmp->next;//переход
        tmp->name = array_names[i];
        tmp->author = array_authors[i];
        tmp->year = array_years[i];
    }
    tmp->next = NULL;
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    if (head == NULL){
        return;
    }

    while (head->next){
        head = head->next;
    }

    head->next = element;
    element->prev = head;
    element->next = NULL;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    if (head == NULL){
        return;
    }

    while (strcmp (head->name,name_for_remove)){
        head = head->next;
        if (head == NULL) {
            return;
        }
    }

    head->prev->next = head->next;
    head->next->prev = head->prev;

    free(head);
}

int count(MusicalComposition* head){
    int count = 0;

    while (head){
        head = head->next;
        count++;
    }
    return count;
}

void print_names(MusicalComposition* head){

    while (head){
        printf("%s\n",head->name);
        head = head->next;
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


