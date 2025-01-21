all: menu.o diff.o sum.o abs_max.o abs_min.o
	gcc menu.o diff.o sum.o abs_max.o abs_min.o -o menu
menu.o: menu.c abs_max.h abs_min.h diff.h sum.h
	gcc -c menu.c
abs_max.o: abs_max.c abs_max.h
	gcc -c abs_max.c
abs_min.o: abs_min.c abs_min.h
	gcc -c abs_min.c
diff.o: diff.c diff.h abs_max.h abs_min.h
	gcc -c diff.c
sum.o: sum.c sum.h
	gcc -c sum.c
clean:
	rm *o. a.out

