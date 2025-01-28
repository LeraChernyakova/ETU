all: main.o double_letters.o q_sort.o replace.o set_color.o text_func.o
	gcc main.o double_letters.o q_sort.o replace.o set_color.o text_func.o -o main

main.o: main.c double_letters.h q_sort.h replace.h set_color.h text_func.h structs.h
	gcc -c main.c

double_letters.o: double_letters.c double_letters.h structs.h
	gcc -c double_letters.c

q_sort.o: q_sort.c q_sort.h structs.h
	gcc -c q_sort.c

replace.o: replace.c replace.h structs.h
	gcc -c replace.c

set_color.o: set_color.c replace.h structs.h
	gcc -c set_color.c

text_func.o: text_func.c replace.h structs.h
	gcc -c text_func.c

clean:
	rm *.o