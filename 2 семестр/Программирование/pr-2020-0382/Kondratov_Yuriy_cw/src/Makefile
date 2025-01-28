all: output_funcs.o processing_funcs.o read_funcs.o main.o
	gcc output_funcs.o processing_funcs.o read_funcs.o main.o -o main
main.o: main.c output_funcs.h processing_funcs.h read_funcs.h structures.h
	gcc -c main.c 
output_funcs.o: output_funcs.c output_funcs.h structures.h
	gcc -c output_funcs.c 
processing_funcs.o: processing_funcs.c processing_funcs.h structures.h
	gcc -c processing_funcs.c 
read_funcs.o: read_funcs.c read_funcs.h processing_funcs.h structures.h
	gcc -c read_funcs.c
clean:
	rm *.o
	
