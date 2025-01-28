all: max.o min.o diff.o sum.o menu.o
	gcc max.o min.o diff.o sum.o menu.o -o menu
menu.o: menu.c max.h min.h diff.h sum.h
	gcc -c menu.c -std=c99
max.o: max.c max.h
	gcc -c max.c -std=c99
min.o: min.c min.h
	gcc -c min.c -std=c99
diff.o: diff.c diff.h max.h min.h
	gcc -c diff.c -std=c99
sum.o: sum.c sum.h min.h
	gcc -c sum.c -std=c99
clean:
	rm *.o