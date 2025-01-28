#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;

    struct MusicalComposition* next;
    struct MusicalComposition* previous;
}MusicalComposition;


// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year); // done

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n); // done

void push(MusicalComposition* head, MusicalComposition* element);

void removeEl(MusicalComposition* head, char* name_for_remove);

int count(MusicalComposition* head);

void print_names(MusicalComposition* head);


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

MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* musical_composition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    musical_composition -> name = name;
    musical_composition -> author = author;
    musical_composition -> year = year;
    musical_composition -> previous = NULL;
    musical_composition -> next = NULL;
    return musical_composition;
}

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition * head;
    MusicalComposition * next;
    for (int i = 0; i < n; i++){
        if(i == 0){
            head = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        }
        else{
            if(i == 1){
                next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
                head -> next = next;
                next -> previous = head;
            }
            else{
                next->next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
                next->next->previous = next;
                next = next->next;
            }
        }
    }
    return head;
}

void push(MusicalComposition* head, MusicalComposition* element){
    MusicalComposition* temp = head;
    while (temp->next != NULL){
        temp = temp -> next;
    }
    temp->next = element;
    element->previous = temp;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* temp = head;
    while (temp != NULL){
        if(strcmp(temp->name, name_for_remove) == 0){
            if(temp->previous != NULL && temp->next != NULL){
                temp->previous->next = temp->next;
                temp->next->previous = temp->previous;
                free(temp);
                break;
            }
            else{
                if(temp->previous == NULL && temp->next != NULL){
                    head = temp->next;
                    temp->next->previous = NULL;
                    free(temp);
                    break ;
                }
                else{
                    if(temp->next == NULL && temp->previous != NULL){
                        temp->previous->next = NULL;
                        free(temp);
                        break;
                    }
                    else{
                        head = NULL;
                        free(temp);
                        break;
                    }
                }
            
            }
        }
        temp = temp->next;
    }
}

int count(MusicalComposition* head){
    if(head == NULL){
        return 0;
    }
    MusicalComposition* temp = head;
    int count = 0;
    while(temp != NULL){
        count+= 1;
        temp = temp->next;
    }
    return count;
}

void print_names(MusicalComposition* head){
    if(head == NULL){
        return ;
    }
    MusicalComposition* temp = head;
    while(temp != NULL){
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}