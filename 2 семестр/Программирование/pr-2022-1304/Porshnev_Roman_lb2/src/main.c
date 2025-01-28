#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct MusicalComposition{

    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
}MusicalComposition;



MusicalComposition* createMusicalComposition(char* name, char* author,int year){

    MusicalComposition* comp  = malloc(sizeof(struct MusicalComposition));
    comp->name = name;
    comp->author = author;
    comp->year = year;
    comp->next = NULL;
    comp->prev = NULL;
    return comp;
}


MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){

    int i;
    MusicalComposition* comp = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    MusicalComposition* now;
    MusicalComposition* tmp = comp;
    for(i = 1; i < n; i++){
        now = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        now->prev = tmp;
        tmp->next = now;
        tmp = now;
    }
    return comp;
}

void push(MusicalComposition* head, MusicalComposition* element){

    while (head->next != NULL){
        head = head->next;
    }
    head->next = element;
    element->prev = head;
}

void removeEl(MusicalComposition* head, char* name_for_remove){

    while(head != NULL){
        if (strcmp(head->name, name_for_remove) == 0){
            head->prev->next = head->next;
            head->next->prev = head->prev;
            free(head);
        }
        head = head->next;
    }

}

int count(MusicalComposition* head){

    int n = 0;
    while (head != NULL){
        head = head->next;
        n++;
    }
    return n;
}

void print_names(MusicalComposition* head){

    while (head != NULL){
        printf("%s\n", head->name);
        head = head->next;
    }
}


int main(){
    int length;
    char c;
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
        fscanf(stdin, "%d", &years[i]);
        fscanf(stdin, "%c", &c);//
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
    fscanf(stdin, "%d", &year_for_push);
    fscanf(stdin, "%c", &c);//
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
