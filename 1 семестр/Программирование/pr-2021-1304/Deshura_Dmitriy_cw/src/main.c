#include"inputtext.h"
#include"formattext.h"
#include<stdio.h>
#include<wchar.h>
#include<locale.h>



int main(){
	setlocale(LC_ALL, "");
	wchar_t **some_strings;
	int n = 0, number_sents, command; //n - счётчик количества text_string
	
	some_strings = input_text(&n);

	struct Sentence *sents;
	sents = make_sentences(n, some_strings, &number_sents);
	number_sents --;

	input_text_free( n, some_strings );
	sents = delete_repeated_sentences(sents, &number_sents);
	
	struct Text text;
	text.sentences = sents;
	text.sents_number = number_sents;
	

	while(1){
		wprintf(L"\033[33mДля продолжения введите номер команды от 1 до 5:\n\t1. В каждом предложении заменить первое слово на второе слово из предыдущего предложения. Для первого предложения, второе слово надо брать из последнего.\n\t2. Отсортировать предложения по длине третьего слова. Если слов меньше трех, то длина третьего слова равняется нулю.\n\t3. Вывести на экран все предложения, в которых в середине слова встречаются цифры. Данные слова нужно выделить зеленым цветом.\n\t4. В каждом предложении, в слове, все символы, которые встречаются несколько раз подряд заменить одним таким символом.\n\t5. Для вывода текущего состояния текста.\nДля завершения программы введите любую другую цифру\n\033[0m");
	
		command = 0;

		wscanf(L"%d", &command);
		switch(command){
			case 1:
				wprintf(L"\033[31mВыполняю команду 1\n\033[0m");
				text = command_1(text);
				break;
			case 2:
				wprintf(L"\033[31mВыполняю команду 2\n\033[0m");
				text = command_2(text);
				break;
			case 3:
				wprintf(L"\033[31mВыполняю команду 3\n\033[0m");
				command_3(text);
				break;
			case 4:
				wprintf(L"\033[31mВыполняю команду 4\n\033[0m");
				text = command_4(text);
				break;
			case 5:
				wprintf(L"\n");
				for(int i = 0; i < text.sents_number; i++)
					wprintf(L"%ls\nwords: %d\n\n", text.sentences[i].str, text.sentences[i].words_number);
				break;
			default:
				wprintf(L"Вы вышли из программы\n");
				return 0;
		}
	}

	
	return 0;
}
