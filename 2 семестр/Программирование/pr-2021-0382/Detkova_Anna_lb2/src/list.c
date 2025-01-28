#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct MusicalComposition{
    struct MusicalComposition* prev;
    char name[80];
    char author[80];
    int year;
    struct MusicalComposition* next;
};

typedef struct MusicalComposition MusicalComposition;

MusicalComposition* createMusicalComposition (char* name, char* author,int year){
    MusicalComposition *res = malloc(sizeof(MusicalComposition));
    res->prev = NULL;
    strcpy(res->name, name);
    strcpy(res->author, author);
    res->year = year;
    res->next = NULL;
    return res;
}

MusicalComposition* createMusicalCompositionList (char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = malloc(sizeof(MusicalComposition));
    MusicalComposition* cur = head;
    MusicalComposition* prev = NULL;
    for (int i=0; i<n; i++){
        cur->prev = prev;
        strcpy(cur->name, array_names[i]);
        strcpy(cur->author, array_authors[i]);
        cur->year = array_years[i];
        prev = cur;
        if (i != n-1) {
            cur = malloc(sizeof(MusicalComposition));
            prev->next = cur;
        }else{
            prev->next = NULL;
        }
    }
    return head;
}

void push (MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* cur = head;
    while(cur->next){
        cur = cur->next;
    }
    cur->next = element;
    element->prev = cur;
    element->next = NULL;
}

void removeEl (MusicalComposition* head, char* name_for_remove){
    MusicalComposition* cur = head;
    while(strcmp(cur->name, name_for_remove)){
        cur = cur->next;
    }
    (cur->next)->prev = cur->prev;
    (cur->prev)->next = cur->next;
    free(cur);
}

int count (MusicalComposition* head){
    int counter = 0;
    MusicalComposition* cur = head;
    while (cur) {
            counter++;
            cur = cur->next;
    }
    return counter;
}

void print_names (MusicalComposition* head){
     MusicalComposition* cur = head;
     while(cur){
         printf("%s\n", cur->name);
         cur = cur->next;
     }
}


int main (){
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
