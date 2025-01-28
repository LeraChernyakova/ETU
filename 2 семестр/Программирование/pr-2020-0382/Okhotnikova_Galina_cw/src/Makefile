all: main.o find_time.o delete_latin_letter.o count_letters.o comp_count_letters.o delete_special_symb.o
	gcc main.o find_time.o delete_latin_letter.o count_letters.o comp_count_letters.o delete_special_symb.o -o main

main.o: main.c find_time.h delete_latin_letter.h count_letters.h comp_count_letters.h  delete_special_symb.h
	gcc -c main.c
find_time.o: find_time.c
	gcc -c find_time.c
delete_latin_letter.o: delete_latin_letter.c
	gcc -c delete_latin_letter.c
count_letters.o: count_letters.c
	gcc -c count_letters.c
comp_count_letters.o: comp_count_letters.c
	gcc -c comp_count_letters.c
delete_special_symb.o: delete_special_symb.c
	gcc -c  delete_special_symb.c
clean: 
	rm *.o
