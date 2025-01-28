kurs: main.o functions.o struct.o text_maker.o
	gcc main.o functions.o struct.o text_maker.o -o kurs

main.o: main.c struct.h
	gcc -c main.c

functions.o: functions.c functions.h
	gcc -c functions.c

struct.o: struct.c struct.h
	gcc -c struct.c

text_maker.o: text_maker.c text_maker.h
	gcc -c text_maker.c

clean:
	rm -rf *.o kurs

