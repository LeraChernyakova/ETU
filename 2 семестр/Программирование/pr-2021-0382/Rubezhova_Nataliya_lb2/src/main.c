#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char name[81];
    char author[81];
    int year;
    struct MusicalComposition* prev;
    struct MusicalComposition* next;
}Elem;

// Создание структуры MusicalComposition

Elem* createMusicalComposition(char* name, char* author,int year){
    Elem* my_elem=(Elem*)malloc(sizeof(Elem));
    strncpy(my_elem->name,name,81);
    strncpy(my_elem->author,author,81);
    my_elem->year=year;
    return my_elem;
}

// Функции для работы со списком MusicalComposition

Elem* createMusicalCompositionList(char** names, char** authors, int* years, int n){
    int i=0;
    Elem* head=createMusicalComposition(names[i],authors[i],years[i]);
    head->prev=NULL;
    Elem* cur=createMusicalComposition(names[i+1],authors[i+1],years[i+1]);
    head->next=cur;
    cur->prev=head;
    Elem* tmp;
    for(i=2;i<n;i++){
        tmp=cur;
        cur=createMusicalComposition(names[i],authors[i],years[i]);
        tmp->next=cur;
        cur->prev=tmp;
    }
    cur->next=NULL;
    return head;
}

void push(Elem* head, Elem* element){
    while(head->next){
        head=head->next;
    }
    head->next=element;
    element->prev=head;
    element->next=NULL;
}

void removeEl(Elem* head, char* name_for_remove){
    while(strcmp(head->name,name_for_remove)!=0){
        head=head->next;
    }
    if(head->next){
        head->prev->next=head->next;
        head->next->prev=head->prev;
    }
    else
        head->prev->next=NULL;
}

int count(Elem* head){
    int c=1;
    while(head->next){
        head=head->next;
        c++;
    }
    return c;
}

void print_names(Elem* head){
    while(head){
        printf("%s\n",head->name);
        head=head->next;
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
    Elem* head = createMusicalCompositionList(names, authors, years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    Elem* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

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
