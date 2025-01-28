all: menu

menu: menu.o abs_max.o abs_min.o diff.o sum.o
	gcc menu.o abs_max.o abs_min.o diff.o sum.o -o menu

menu.o: menu.c
	gcc -c menu.c

abs_max.o: abs_max.c
	gcc -c abs_max.c

abs_min.o: abs_min.c
	gcc -c abs_min.c

diff.o: diff.c
	gcc -c diff.c

sum.o: sum.c
	gcc -c sum.c

clean:
	rm -rf *.o menu
