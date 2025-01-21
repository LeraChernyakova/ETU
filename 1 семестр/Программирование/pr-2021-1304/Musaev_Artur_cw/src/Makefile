all: main.o inputoutput.o processing.o
	gcc main.o inputoutput.o processing.o


main.o: main.c inputoutput.h
	gcc -c main.c 
	

inputoutput.o: inputoutput.c inputoutput.h
	gcc -c inputoutput.c

processing.o: processing.c processing.h
	gcc -c processing.c
	
	
clean:
	rm *.o 
