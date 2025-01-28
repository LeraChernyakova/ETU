all: menu.o abs_max.o abs_min.o diff.o sum.o
	gcc menu.o abs_max.o abs_min.o diff.o sum.o -o menu
menu.o: menu.c
	gcc -c menu.c -std=c99
abs_max.o: abs_max.c
	gcc -c abs_max.c -std=c99
abs_min.o: abs_min.c
	gcc -c abs_min.c -std=c99
diff.o: diff.c
	gcc -c diff.c -std=c99
sum.o: sum.c
	gcc -c sum.c -std=c99
clean:
	rm -rf *.o menu
