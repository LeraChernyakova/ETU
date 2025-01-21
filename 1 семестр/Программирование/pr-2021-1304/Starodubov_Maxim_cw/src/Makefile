all: main.o main_functionality.o time_diffs.o useful.o get_text.o structs.h main_functionality.h time_diffs.h useful.h get_text.h colors.h
	gcc main.o main_functionality.o time_diffs.o useful.o get_text.o -o coursework

main.o: main.c structs.h main_functionality.h time_diffs.h useful.h get_text.h colors.h
	gcc -c main.c

main_functionality.o: main_functionality.c structs.h main_functionality.h
	gcc -c main_functionality.c

time_diffs.o: time_diffs.c structs.h time_diffs.h colors.h
	gcc -c time_diffs.c

useful.o: useful.c structs.h useful.h colors.h
	gcc -c useful.c

get_text.o: get_text.c structs.h get_text.h
	gcc -c get_text.c

clean:
	rm *.o coursework
