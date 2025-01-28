all: menu.o task_1.o task_2.o task_3.o task_4.o Input.o
	gcc -g menu.o task_1.o task_2.o task_3.o task_4.o Input.o -o menu
menu.o: menu.c task_1.h task_2.h task_3.h task_4.h structs.h Input.h
	gcc -g -c menu.c
task_1.o: task_1.c task_1.h structs.h
	gcc -g -c task_1.c
task_2.o: task_2.c task_2.h structs.h
	gcc -c task_2.c
task_3.o: task_3.c task_3.h structs.h
	gcc -c task_3.c
task_4.o: task_4.c task_4.h structs.h
	gcc -c task_4.c
Input.o: Input.c Input.h structs.h
	gcc -c Input.c
clean:
	rm *.o menu