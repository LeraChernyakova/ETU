#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition {
    char* name;
    char* author;
    int year;
    struct MusicalComposition* previous;
    struct MusicalComposition* next;
} MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author, int year){
    MusicalComposition* mcomp = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    mcomp->name = name;
    mcomp->author = author;
    mcomp->year = year;
    mcomp->previous = NULL;
    mcomp->next = NULL;
    return mcomp;
}

// Функции для работы со списком MusicalComposition

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* end = head;
    while (end->next != NULL){
        end = end->next;
    }
    end->next = element;
    element->previous = end;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    int i;
    MusicalComposition* new_element;
    MusicalComposition* list = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    for (i = 1; i < n; i++){
        new_element = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        push(list, new_element);
    }
    return list;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* needful_elem = head;
    while (strcmp(needful_elem->name, name_for_remove)){
        needful_elem = needful_elem->next;
    }
    if (needful_elem->previous != NULL){
        needful_elem->previous->next = needful_elem->next;
    }
    if (needful_elem->next != NULL){
        needful_elem->next->previous = needful_elem->previous;
    }
    free(needful_elem);
}

int count(MusicalComposition* head){
    MusicalComposition* current = head;
    int i = 1;
    while ((current = current->next) != NULL){
        i++;
    }
    return i;
}


void print_names(MusicalComposition* head){
    MusicalComposition* current = head;
    while (current != NULL){
        printf("%s\n", current->name);
        current = current->next;    
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