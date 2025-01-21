all: menu.o max_num.o min_num.o diff_num.o sum_num.o 
	gcc menu.o max_num.o min_num.o diff_num.o sum_num.o -o menu
menu.o: menu.c max_num.h min_num.h diff_num.h sum_num.h
	gcc -c menu.c 
ax_num.o: max_num.c max_num.h
	gcc -c max_num.c
min_num.o: min_num.c min_num.h
	gcc -c min_num.c
diff_num.o: diff_num.c max_num.h min_num.h diff_num.h
	gcc -c diff_num.c
sum_nums.o: sum_num.c min_num.h sum_num.h
	gcc -c sum_num.c
clean:
	rm -r menu menu.o max_num.o min_num.o diff_num.o sum_num.o
