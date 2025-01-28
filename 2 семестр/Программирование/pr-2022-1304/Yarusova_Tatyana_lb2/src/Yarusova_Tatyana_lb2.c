#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition{
    char* name;
    char* author;
    int year;
    struct MusicalComposition* next;
    struct MusicalComposition* previous;
} MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* author,int year){
    MusicalComposition* mc = (MusicalComposition*)malloc(sizeof(MusicalComposition));
    mc->name = name;
    mc->author = author;
    mc->year = year;
    mc->next = NULL;
    mc->previous = NULL;
    return mc;
}


MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n){
    MusicalComposition* head;
    MusicalComposition* next;
    for(int i = 0; i < n; i++){
        if(i == 0)
            head = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
        else{
            if(i == 1){
                next = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
                head->next = next;
                next->previous = head;
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
    MusicalComposition* current = head;
    while(current->next != NULL){
        current = current->next;
    }
    element->previous = current;
    current->next = element;
}

void removeEl(MusicalComposition* head, char* name_for_remove){
    MusicalComposition* current = head;
    while(current != NULL){
        if((strcmp(current->name,name_for_remove)) == 0){
		if(current->next == NULL){
			current->previous->next = NULL;
			free(current);
		}
		else{
            		current->previous->next = current->next;
            		current->next->previous = current->previous;
            		free(current);
            		break;
        	}
	}
        current  = current->next;
    }
    
}

int count(MusicalComposition* head){
    MusicalComposition* current = head;
    int count = 0;
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}

void print_names(MusicalComposition* head){
    MusicalComposition* current = head;
    while(current != NULL){
        printf("%s\n",current->name);
        current = current->next;
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
/*7
Fields of Gold
Sting
1993
In the Army Now
Status Quo
1986
Mixed Emotions
The Rolling Stones
1989
Billie Jean
Michael Jackson
1983
Seek and Destroy
Metallica
1982
Wicked Game
Chris Isaak
1989
Points of Authority
Linkin Park
2000
Sonne
Rammstein
2001
Sonne*/