all: abs_max.o abs_min.o diff.o sum.o menu.o
	gcc abs_max.o abs_min.o diff.o sum.o menu.o -o menu
abs_max.o: abs_max.c max.h
	gcc -c abs_max.c
abs_min.o: abs_min.c min.h
	gcc -c abs_min.c
diff.o: diff.c diff.h
	gcc -c diff.c
sum.o: sum.c sum.h
	gcc -c sum.c
menu.o: menu.c
	gcc -c menu.c
	
