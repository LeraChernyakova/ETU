CC=gcc
CFLAGS= -I.
DEPS = input.h stringsOperations.h textStructures.h output.h
OBJ = main.o input.o stringsOperations.o output.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

editText: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(OBJ)

