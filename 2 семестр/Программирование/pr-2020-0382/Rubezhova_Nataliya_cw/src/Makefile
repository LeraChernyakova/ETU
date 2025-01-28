all: input_f.o task_1.o task_2.o task_3.o task_4.o menu.o
	gcc input_f.c task_1.c task_2.c task_3.c task_4.c menu.c -o menu
input_f.o: input_f.c input_f.h
	gcc -c input_f.c
task_1.o: task_1.c task_1.h
	gcc -c task_1.c
task_2.o: task_2.c task_2.h
	gcc -c task_2.c
task_3.o: task_3.c task_3.h
	gcc -c task_3.c
task_4.o: task_4.c task_4.h
	gcc -c task_4.c
menu.o: menu.c input_f.h task_1.h task_2.h task_3.h task_4.h
	gcc -c menu.c
clean:
	rm *.o menu
