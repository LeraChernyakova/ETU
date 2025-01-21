#include "structs.h"
#include "useful.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>

void print_text(struct Text* text, wchar_t sep)
{
	setlocale(LC_ALL, "");

	wprintf(L"%s\n", TEXT_OTPUT);
	for (int i = 0; i < text->size-1; i++)
	{
		wprintf(text->content[i].content);
		wprintf(L"%c", sep);
	}
	wprintf(text->content[text->size-1].content);
	wprintf(L"%s\n\n", NORMAL);
}

void free_text(struct Text* text)
{
	setlocale(LC_ALL, "");

	for (int i = 0; i < text->size; i++)
	{
		free(text->content[i].content);
	}
	free(text->content);
}

void output_request(struct Text* text)
{	
	setlocale(LC_ALL, "");

	int command = 0;
	wprintf(L"%sУспешно!%s\nВывесте результат на экран? Если да, то введите '1'\n>>> ", SUCCESS, NORMAL);
	wscanf(L"%d", &command);
	if (command == 1)
	{
		print_text(text, ' ');
	}
}
