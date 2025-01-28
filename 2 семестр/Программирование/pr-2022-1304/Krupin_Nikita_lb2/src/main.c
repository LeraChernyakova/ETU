#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Описание структуры MusicalComposition
typedef struct MusicalComposition{
    char *name, *author;
    int year;
    struct MusicalComposition *next, *prev;
} MusicalComposition;

// Создание структуры MusicalComposition
MusicalComposition* createMusicalComposition(char* name, char* author,
																	int year){
    MusicalComposition* newMC = malloc(sizeof(MusicalComposition));
    newMC->name = name;
    newMC->author = author;
    newMC->year = year;
    
    return newMC;
}

// Функции для работы со списком MusicalComposition
MusicalComposition* createMusicalCompositionList(char** array_names,
							char** array_authors, int* array_years, int n){
	if (n <= 0) return NULL;
	
	MusicalComposition* head = createMusicalComposition(array_names[0],
											array_authors[0], array_years[0]);
	MusicalComposition* tail = head;
	head->prev = NULL;
    for (int i = 1; i < n; i++){
        tail->next = createMusicalComposition(array_names[i],
        									array_authors[i], array_years[i]);
        tail->next->prev = tail;
        tail = tail->next;
    }
    tail->next = NULL;
    
    return head;
}

void push(MusicalComposition** p_head, MusicalComposition* element){
	MusicalComposition* last = *p_head;
    if (last){
	    while (last->next) last = last->next;
	    last->next = element;
    } else *p_head = element;
    element->prev = last;
    element->next = NULL;
}

void removeEl(MusicalComposition** p_head, char* name_for_remove){
	MusicalComposition* current = *p_head;
	MusicalComposition* temp = NULL;
	while (current)
		if (!strcmp(current->name, name_for_remove)){
			if (current->next) current->next->prev = current->prev;
			if (current->prev) current->prev->next = current->next;
			else *p_head = current->next;
			temp = current;
			current = current->next;
			free(temp);
		} else current = current->next;
}

int count(MusicalComposition* head){
	int count = 0;
	while (head){
		head = head->next;
		count++;
	}
	
	return count;
}

void print_names(MusicalComposition* head){
	while (head){
		puts(head->name);
		head = head->next;
	}
}

// Основная программа
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

        names[i] = (char*)malloc(sizeof(char) * (strlen(name)+1));
        authors[i] = (char*)malloc(sizeof(char) * (strlen(author)+1));

        strcpy(names[i], name);
        strcpy(authors[i], author);

    }
    MusicalComposition* head = createMusicalCompositionList(names, authors,
                                                                years, length);
    char name_for_push[80];
    char author_for_push[80];
    int year_for_push;

    char name_for_remove[80];

    fgets(name_for_push, 80, stdin);
    fgets(author_for_push, 80, stdin);
    fscanf(stdin, "%d\n", &year_for_push);
    (*strstr(name_for_push,"\n"))=0;
    (*strstr(author_for_push,"\n"))=0;

    MusicalComposition* element_for_push = createMusicalComposition
                            (name_for_push, author_for_push, year_for_push);

    fgets(name_for_remove, 80, stdin);
    (*strstr(name_for_remove,"\n"))=0;

    if (head) printf("%s %s %d\n", head->name, head->author, head->year);
    int k = count(head);

    printf("%d\n", k);
    push(&head, element_for_push);

    k = count(head);
    printf("%d\n", k);

    removeEl(&head, name_for_remove); 
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
