#include "structs.h"
#include "time_diffs.h"
#include "colors.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void print_time_diffs(struct Text* text)
{
	setlocale(LC_ALL, "");

	time_t now = time(NULL);
	struct tm* this_time = localtime(&now);
	int time_now = this_time->tm_hour*60 + this_time->tm_min;

	int time = 0;
	int index;
	int counter = 0;

	wprintf(L"%s\n", TEXT_OTPUT);
	for (int i = 0; i < text->size; i++)
	{
		index = 2;
		time = find_time_diff(&text->content[i], &index);
		while (time >= 0)
		{
			wprintf(L"Подстрока найдена в предложении %d, разница с текущим временем: %d.\n", i+1, abs(time-time_now));
			time = find_time_diff(&text->content[i], &index);
			counter++;
		}
	}
	if (counter == 0)
	{
		wprintf(L"Не найдено\n");
	}
	wprintf(L"%s\n", NORMAL);
}

int find_time_diff(struct Sentence* sentence, int* index)
{
	setlocale(LC_ALL, "");

	int hours, minutes;
	for (int i = *index; i < sentence->size-3; i++)
	{
		if (sentence->content[i] == ':' && (iswdigit(sentence->content[i-2]) && iswdigit(sentence->content[i-1]) && iswdigit(sentence->content[i+1]) && iswdigit(sentence->content[i+2])) && ((i-2 == 0 || iswalnum(sentence->content[i-3]) == 0) && (iswalnum(sentence->content[i+3]) == 0)))
		{
			hours = (sentence->content[i-2]-'0')*10 + (sentence->content[i-1]-'0');
			minutes = (sentence->content[i+1]-'0')*10 + (sentence->content[i+2]-'0');
			if (hours < 24 && minutes < 60)
			{
				*index = i + 6;
				return hours*60 + minutes;
			}
		}
	}
	return -1;
}
