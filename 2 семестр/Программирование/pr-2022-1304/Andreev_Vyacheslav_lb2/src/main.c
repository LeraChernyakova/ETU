#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//................................MusicalComposition.......................................//

typedef struct MusicalComposition
{
    char* name;
    char* author;
    int year;

    struct MusicalComposition* next;
    struct MusicalComposition* previous;
} MusicalComposition;

MusicalComposition* createMusicalComposition(char* name, char* autor, int year);
MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n);
void push(MusicalComposition* head, MusicalComposition* element);
void removeEl(MusicalComposition* head, char* name_for_remove);
int count(MusicalComposition* head);
void print_names(MusicalComposition* head);



MusicalComposition* createMusicalComposition(char* name, char* autor, int year)
{
    if(name == NULL || autor == NULL) return NULL;

    MusicalComposition* LComposition = (MusicalComposition*)malloc( sizeof(MusicalComposition) );
    LComposition->name = name;
    LComposition->author = autor;
    LComposition->year = year;
    LComposition->next = NULL;
    LComposition->previous = NULL;

    return LComposition;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
    if(array_names == NULL || array_authors == NULL || array_years == NULL || n <= 0) return NULL;

    MusicalComposition* LHead = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
    if(LHead == NULL) return NULL;

    for(int i = 1; i < n; ++i)
    {
        push(LHead, createMusicalComposition(array_names[i], array_authors[i], array_years[i]));
    }

    return LHead;
}

void push(MusicalComposition* head, MusicalComposition* element)
{
    if(head == NULL || element == NULL) return;

    while(head->next != NULL)
    {
        head = head->next;
    }

    head->next = element;
    element->previous = head;
}

void removeEl(MusicalComposition* head, char* name_for_remove)
{
    if(name_for_remove == NULL) return;

    while(head != NULL)
    {
        if(strcmp(head->name, name_for_remove) == 0)
        {
            if(head->previous != NULL) head->previous->next = head->next;
            head->next->previous = head->previous;
            free(head);
            return;
        }

        head = head->next;
    }
}

int count(MusicalComposition* head)
{
    int Result = 0;
    while(head != NULL)
    {
        ++Result;
        head = head->next;
    }

    return Result;
}

void print_names(MusicalComposition* head)
{
    while(head != NULL)
    {
        puts(head->name);
        head = head->next;
    }
}

//.........................................................................................//



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
