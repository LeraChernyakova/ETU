all: menu.o min.o max.o diff.o sum.o
	gcc menu.o min.o max.o diff.o sum.o -o menu

menu.o: menu.c min.h max.h diff.h sum.h
	gcc -c menu.c

min.o: min.c min.h
	gcc -c min.c

max.o: max.c max.h
	gcc -c max.c

diff.o: diff.c diff.h max.h min.h
	gcc -c diff.c

sum.o: sum.c sum.h min.h
	gcc -c sum.c
