all: Krupin_Nikita_cw

Krupin_Nikita_cw: main.o txtio.o txtproc.o
	gcc main.o txtio.o txtproc.o -o Krupin_Nikita_cw

main.o: main.c txtio.h txtproc.h
	gcc -c main.c

txtio.o: txtio.c txtio.h
	gcc -c txtio.c

txtproc.o: txtproc.c txtproc.h
	gcc -c txtproc.c

clean:
	rm -rf *.o Krupin_Nikita_cw
