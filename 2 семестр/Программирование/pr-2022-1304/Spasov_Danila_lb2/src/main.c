#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct MusicalComposition 
{
	char* name;
	char* author;
	int year;
	struct MusicalComposition* previous;
	struct MusicalComposition* next;
}
MusicalComposition;


MusicalComposition* createMusicalComposition(char* name, char* author, int year)
{
	MusicalComposition* new_song = malloc(sizeof(MusicalComposition));
	new_song->author = author;
	new_song->name = name;
	new_song->year = year;
	new_song->previous = NULL;
	new_song->next = NULL;
	return new_song;
}


MusicalComposition* createMusicalCompositionList(char** array_names, char** array_authors, int* array_years, int n)
{
	MusicalComposition* head = createMusicalComposition(array_names[0], array_authors[0], array_years[0]);
	MusicalComposition* song_1;
	MusicalComposition* song_2;
	song_1 = head;
	for (int i = 1; i < n; i++)
	{
		song_2 = createMusicalComposition(array_names[i], array_authors[i], array_years[i]);
		song_1->next = song_2;
		song_2->previous = song_1;
		song_1 = song_1->next;
	}
	return head;
}


void push(MusicalComposition* head, MusicalComposition* element)
{
	if (!head)
		head = element;
	else 
	{
		while (head->next)
			head = head->next;
		head->next = element;
		element->previous = head;
	}
}


void removeEl(MusicalComposition* head, char* name_for_remove)
{
	MusicalComposition* elem;
	if(head)
		while(head->next)
		{
			if (!strcmp(head->name, name_for_remove))
			{
				elem = head;
				head = head->next;
				head->previous = elem->previous;
				free(elem);
				elem = head->previous;
				elem->next = head;
			}
			else
				head = head->next;
		}
}


int count(MusicalComposition* head)
{
	int songs_counter = 0;
	if (!head)
		return 0;
	while (head->next)
	{
		head = head->next;
		songs_counter++;
	}
	return songs_counter + 1;
}


void print_names(MusicalComposition* head)
{
	while (head)
	{
		printf("%s\n", head->name);
		head = head->next;
	}
}


int main()
{
	int length;
	scanf("%d\n", &length);

	char** names = (char**)malloc(sizeof(char*) * length);
	char** authors = (char**)malloc(sizeof(char*) * length);
	int* years = (int*)malloc(sizeof(int) * length);

	for (int i = 0; i < length; i++)
	{
		char name[80];
		char author[80];

		fgets(name, 80, stdin);
		fgets(author, 80, stdin);
		fscanf(stdin, "%d\n", &years[i]);

		(*strstr(name, "\n")) = 0;
		(*strstr(author, "\n")) = 0;

		names[i] = (char*)malloc(sizeof(char*) * (strlen(name) + 1));
		authors[i] = (char*)malloc(sizeof(char*) * (strlen(author) + 1));

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
	(*strstr(name_for_push, "\n")) = 0;
	(*strstr(author_for_push, "\n")) = 0;

	MusicalComposition* element_for_push = createMusicalComposition(name_for_push, author_for_push, year_for_push);

	fgets(name_for_remove, 80, stdin);
	(*strstr(name_for_remove, "\n")) = 0;

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

	for (int i = 0; i < length; i++) {
		free(names[i]);
		free(authors[i]);
	}
	free(names);
	free(authors);
	free(years);

	return 0;

}