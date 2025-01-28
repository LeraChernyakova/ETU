all: menu.o abs_min.o abs_max.o diff.o sum.o
	gcc menu.o abs_min.o abs_max.o diff.o sum.o -o menu
menu.o: abs_min.o abs_max.o diff.o sum.o
	gcc -c menu.c -std=c99
abs_min.o: abs_min.c abs_min.h
	gcc -c abs_min.c -std=c99
abs_max.o: abs_max.c abs_max.h
	gcc -c abs_max.c -std=c99
diff.o: diff.c diff.h
	gcc -c diff.c -std=c99
sum.o: sum.c sum.h
	gcc -c sum.c -std=c99
clean:
	rm  *.o