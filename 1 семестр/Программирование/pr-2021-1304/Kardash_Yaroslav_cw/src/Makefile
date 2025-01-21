all: main.o inp_out_free.o processing.o
	gcc main.o inp_out_free.o processing.o -o prog
main.o: main.c
	gcc -c main.c
inp_out_free.o: inp_out_free.c
	gcc -c inp_out_free.c
processing.o: processing.c
	gcc -c processing.c
