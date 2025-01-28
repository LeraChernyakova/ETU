#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct MusicalComposition{
    char name[80];
    char author[80];
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* prev;
}MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* author, int year)
{
    MusicalComposition* cur = malloc(sizeof(MusicalComposition));
    strcpy(cur->name, name);
    strcpy(cur->author, author);
    cur->year = year;
    cur->next=NULL;
    cur->prev=NULL;
    return cur;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* cur;
    MusicalComposition* last;
    MusicalComposition* first;
    int flag=1;
    int i;
    for(i=0;i<n;i++){
        cur=createMusicalComposition(array_names[i],array_authors[i],array_years[i]);
        if (flag){
            first=cur;
            flag=0;
            last=first;
            continue;
        }
        cur->prev=last;
        last->next=cur;
        last=cur;
    }
    return first;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* tmp = head;
    while (1){
        if (tmp->next==NULL){
            element->prev = tmp;
            tmp->next = element;
            break;
        }
        tmp=tmp->next;
    }
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* tmp = head;
    while (tmp){
        if (strcmp(tmp->name,name_for_remove)==0){
            tmp->next->prev=tmp->prev;
            tmp->prev->next = tmp->next;
            free(tmp);
        }
        tmp=tmp->next;
    }
}

int count(MusicalComposition* head){
    int counter=0;
    MusicalComposition* tmp = head;
    while (tmp){
        counter++;
        tmp=tmp->next;
    }
    return counter;
}

void print_names(MusicalComposition* head){
    MusicalComposition* tmp = head;
    while(tmp){
        printf("%s\n",tmp->name);
        tmp=tmp->next;
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