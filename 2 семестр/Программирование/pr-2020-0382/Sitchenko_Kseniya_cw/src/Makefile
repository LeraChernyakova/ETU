main: main.o .o in_n_out.o changes.o date.o 
	gcc main.o .o in_n_out.o changes.o date.o -o main
 main.o: main.c 
	gcc -c main.c 
  in_n_out.o: in_n_out.c 
	gcc -c in_n_out.c 
 abs_min.o: abs_min.c 
	gcc -c abs_min.c 
  changes.o: changes.c 
	gcc -c changes.c 
  date.o: date.c 
	gcc -c date.c 
 clean: 
	rm *.o main
