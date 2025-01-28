#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

#include "structures.h"

#define TRUE 1
#define FALSE 0
#define SENT_STEP 50
#define TEXT_STEP 5
#define EOINP L'\0'

#define RESET_C L"\033[0m"
#define RED L"\033[1;91m"
#define BLUE L"\033[1;94m"
#define GREEN L"\033[1;92m"
#define YELLOW L"\033[1;93m"



void put_printed_sent(struct Sentence sent);

void put_sent_without_numbers(struct Sentence sent);

int put_start_end_upper_words(struct Sentence sent);
