#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct MusicalComposition{
    char name[80];
    char author[80];
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* previous;
}MusicalComposition;// Создание структуры MusicalComposition


MusicalComposition* createMusicalComposition(char* name, char* autor,int year){
    MusicalComposition* composition = (MusicalComposition*) malloc(sizeof (MusicalComposition));
    strcpy(composition->name, name);
    strcpy(composition->author, autor);
    composition->year = year;
    composition->next = NULL;
    composition->previous = NULL;

    return composition;
};

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = (MusicalComposition*) malloc(sizeof (MusicalComposition));
    MusicalComposition* tmp;
    MusicalComposition* buf;
    head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    head->previous = NULL;
    for(int i = 1; i < n; i++){
        buf = tmp;
        tmp = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        if(i == 1){
            head->next = tmp;
            tmp->previous = head;
        } else{
            buf->next = tmp;
            tmp->previous = buf;
        }

    }

    return head;
};

int count(MusicalComposition* head){
    int count = 0;
    MusicalComposition* element = head;
    if(element == NULL){
        return count;
    }
    else{
        count++;
    }
    while(element->next != NULL){
        count++;
        element = element->next;
    }
    return count;
};

void push(MusicalComposition* head, MusicalComposition* element){
    int number = count(head);
    MusicalComposition* tmp = head;
    for(int i = 1; i < number; i++){
        tmp = tmp->next;
    }
    tmp->next = element;
    tmp->next->next = NULL;
    tmp->next->previous = tmp;

};

void removeEl(MusicalComposition* head, char* name_for_remove){
    int number = count(head);
    MusicalComposition* tmp = head;
    for(int i = 0; i < number; i++){
        if(!strcmp(tmp->name, name_for_remove)) {
            if(i == number - 1){
                tmp->previous->next = NULL;
                free(tmp);
                break;
            }
            else {
                tmp->previous->next = tmp->next;
                tmp->next->previous = tmp->previous;
                free(tmp);
                break;
            }
        }
        tmp = tmp->next;
    }
};



void print_names(MusicalComposition* head) {
    int number = count(head);
    MusicalComposition *tmp = head;
    for(int i = 0; i < number; i++){
        puts(tmp->name);
        tmp = tmp->next;
    }
};


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
