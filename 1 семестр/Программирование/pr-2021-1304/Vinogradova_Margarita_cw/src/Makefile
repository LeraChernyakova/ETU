all: main.o text_processing.o
	gcc main.o text_processing.o 

main.o: main.c text_processing.h
	gcc -c main.c

text_processing.o: text_processing.c text_processing.h
	gcc -c text_processing.c

clean:
	rm *.o a.out
