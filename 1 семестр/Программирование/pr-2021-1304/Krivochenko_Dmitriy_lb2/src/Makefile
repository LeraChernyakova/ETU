all: abs_max.o abs_min.o diff.o sum.o menu.o 
	gcc abs_max.o abs_min.o diff.o sum.o menu.o -o menu
abs_max.o: abs_max.c
	gcc -c -std=c99 abs_max.c
abs_min.o: abs_min.c
	gcc -c -std=c99 abs_min.c
diff.o: diff.c
	gcc -c -std=c99 diff.c
sum.o: sum.c
	gcc -c -std=c99 sum.c
menu.o: menu.c
	gcc -c -std=c99 menu.c
