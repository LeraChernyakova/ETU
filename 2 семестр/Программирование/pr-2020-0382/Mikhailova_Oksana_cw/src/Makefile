all: main.o input_text.o funcs_for_tasks.o other_funcs.o 
	gcc main.o input_text.o funcs_for_tasks.o other_funcs.o -o main
input_text.o: input_text.c structures.h
	gcc -c input_text.c 
funcs_for_tasks.o: funcs_for_tasks.c structures.h
	gcc -c funcs_for_tasks.c
other_funcs.o: other_funcs.c structures.h
	gcc -c other_funcs.c
main.o: main.c input_text.h funcs_for_tasks.h other_funcs.c structures.h
	gcc -c main.c
clean:
	rm *.o
