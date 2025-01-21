all: main.o first_func.o second_func.o third_func.o fourth_func.o textio.o
	gcc main.o first_func.o second_func.o third_func.o fourth_func.o textio.o -o program

textio.o: textio.c 
	gcc -c textio.c 

first_func.o: first_func.c textio.h 
	gcc -c first_func.c

second_func.o: second_func.c textio.h 
	gcc -c second_func.c 

third_func.o: third_func.c textio.h
	gcc -c third_func.c 

fourth_func.o: fourth_func.c textio.h
	gcc -c fourth_func.c

main.o: main.c textio.h all_funcs.h 
	gcc -c main.c

clean:
	rm -rf *.o program
