all: output_funcs.o text_changing.o input_funcs.o main.o
	gcc output_funcs.o text_changing.o input_funcs.o main.o
main.o: output_funcs.h text_changing.h input_funcs.h structures.h main.c
	gcc -c main.c 
input_funcs.o: input_funcs.c input_funcs.h structures.h
	gcc -c input_funcs.c
text_changing.o: text_changing.c text_changing.h structures.h
	gcc -c text_changing.c
output_funcs.o: output_funcs.c output_funcs.h structures.h
	gcc -c output_funcs.c
clean:
	rm *.o
