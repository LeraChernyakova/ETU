#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>



// Описание структуры MusicalComposition
typedef struct Node{
    char name[80];
    char author[80];
    int year;

    struct Node* next;
    struct Node* prev;

}MusicalComposition;


// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* tmp = malloc(sizeof(MusicalComposition));

    strcpy(tmp->name, name);
    strcpy(tmp->author, author);
    tmp->year = year;

    tmp->next = NULL;
    tmp->prev = NULL;

    return tmp;

}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head = createMusicalComposition(*array_names, *array_authors, *array_years);

    MusicalComposition* tmp = head;
    MusicalComposition* current;

    for (int i = 0; i<n; i++){
        current = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);

        tmp->next = current;
        current->prev = tmp;

        tmp = current;

    }

    return head;

}

void push(MusicalComposition* head, MusicalComposition* element) {
    MusicalComposition* tmp = head;
    while(1){
        if (tmp->next == NULL) {
            tmp->next = element;
            element->prev = tmp;
            break;
        }else {
            tmp = tmp->next;
        }
    }

}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* tmp;
    tmp = head;
    while(strcmp(tmp->name, name_for_remove) != 0){
        tmp = tmp->next;
    }
    tmp->prev->next = tmp->next;

}

int count(MusicalComposition* head){
   MusicalComposition* tmp = head;
   int i = 0;
   while (tmp->next != NULL){
       tmp = tmp->next;
       i++;
   }
   return i;
}

void print_names(MusicalComposition* head){
    MusicalComposition* tmp = head;

    while (tmp->next != NULL){
        printf("%s\n", tmp->next->name);
        tmp = tmp->next;
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
    //!!!
    //print_names(head);

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
