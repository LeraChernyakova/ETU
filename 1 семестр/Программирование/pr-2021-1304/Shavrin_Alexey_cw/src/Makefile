CC = gcc

all: main.o input_output_text_functions.o text_processing_functions.o
	$(CC) main.o input_output_text_functions.o text_processing_functions.o -o main


main.o: main.c input_output_text_functions.h text_processing_functions.h my_struct.h
	$(CC) -c main.c


input_output_text.o: input_output_text_functions.c text_processing_functions.h my_struct.h
	$(CC) -c input_output_text_functions.c


text_processing_functions.o: text_processing_functions.c my_struct.h
	$(CC) -c text_processing_functions.c


clean:
	rm -r *.o
