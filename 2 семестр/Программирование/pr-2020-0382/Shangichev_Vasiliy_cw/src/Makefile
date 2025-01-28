all: main.o string_functions.o functions_for_text.o functions_for_sentence.o
	gcc main.o string_functions.o functions_for_text.o functions_for_sentence.o -o program

main.o: main.c
	gcc -c main.c

string_functions.o: string_functions.c
	gcc -c string_functions.c

functions_for_text.o: functions_for_text.c
	gcc -c functions_for_text.c

functions_for_sentence.o: functions_for_sentence.c
	gcc -c functions_for_sentence.c

clean:
	rm -f *.o 

