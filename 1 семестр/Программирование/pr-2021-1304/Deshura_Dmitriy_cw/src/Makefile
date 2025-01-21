all:	main.o inputtext.o formattext.o
	gcc main.o inputtext.o formattext.o -o run

main.o:	main.c inputtext.h formattext.h
	gcc -c main.c

inputtext.o:	inputtext.c inputtext.h
	gcc -c inputtext.c

formattext.o:	formattext.c formattext.h
	gcc -c formattext.c

clean:
	rm -rf *.o run
