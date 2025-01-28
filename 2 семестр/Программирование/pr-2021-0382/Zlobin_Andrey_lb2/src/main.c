#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Описание структуры MusicalComposition
typedef struct MusicalComposition{
	char * name;
	char * author;
	int year;
	struct MusicalComposition * next;
}MusicalComposition;

// Создание структуры MusicalComposition

MusicalComposition* createMusicalComposition(char* name, char* author,int year){	
	MusicalComposition* newComposition = (MusicalComposition*)malloc(sizeof(MusicalComposition));
	newComposition -> name = name;
	newComposition -> author = author;
	newComposition -> year = year;
	newComposition -> next = NULL;
	return newComposition;
	}

// Функции для работы со списком MusicalComposition

MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){

	MusicalComposition* newComposition = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
	MusicalComposition* begin = newComposition;
	
	for (int i = 0; i < n; i++) {
		newComposition -> next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
		newComposition = newComposition -> next;
	}
	return begin;
}

void push(MusicalComposition* head, MusicalComposition* element){
	while (head -> next != NULL){
		head = head -> next;
	}
	head -> next = element;
}


void removeEl(MusicalComposition* head, char* name_for_remove){
	MusicalComposition* prev = NULL;
	while (strcmp(head -> name, name_for_remove) && head -> next != NULL){
		prev = head;
		head = head -> next;
	}
	
	if (prev != NULL) {
	    head = head -> next;
	    free(prev -> next -> name);
	    free(prev -> next -> author);
	    free(prev -> next);
	    prev -> next = head;
	} else {
	    prev = head;
	    head = head -> next;
	    free(prev -> name);
	    free(prev -> author);
	    free(prev);
	}
}




int count(MusicalComposition* head){
	int i = 0;
	while (head -> next != NULL){
		head = head -> next;
		i++;
	}
	return i;
}


void print_names(MusicalComposition* head){
while (head -> next != NULL){
		head = head -> next;
		printf("%s\n", head -> name);
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