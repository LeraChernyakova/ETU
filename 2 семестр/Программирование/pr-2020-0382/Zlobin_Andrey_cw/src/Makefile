all: input.o print_dict.o change_symb.o sort_lat.o del_sent_spec.o main.o
	gcc input.o print_dict.o change_symb.o sort_lat.o del_sent_spec.o main.o -o main
main.o: main.c input.h print_dict.h change_symb.h sort_lat.h del_sent_spec.h text_struct.h
	gcc -c main.c 
input.o: input.c input.h text_struct.h
	gcc -c input.c 
print_dict.o: print_dict.c print_dict.h text_struct.h
	gcc -c print_dict.c 
change_symb.o: change_symb.c change_symb.h text_struct.h
	gcc -c change_symb.c
sort_lat.o: sort_lat.c sort_lat.h text_struct.h
	gcc -c sort_lat.c
del_sent_spec.o: del_sent_spec.c del_sent_spec.h text_struct.h
	gcc -c del_sent_spec.c
clean:
	rm *.o
