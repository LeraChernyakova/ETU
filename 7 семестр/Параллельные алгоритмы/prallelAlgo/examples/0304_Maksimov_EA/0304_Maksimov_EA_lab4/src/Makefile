CC = g++
CFLAGS = -g -Wall -MMD -D_REENTRANT

BIN_PTHREADS = ./bin/pthreads.exe
BIN_STRASSEN = ./bin/strassen.exe

CPP_PTHREADS = ./pthreads/main.cpp ./pthreads/pthreads.cpp ./model/matrix.cpp ./io/input.cpp ./io/output.cpp
CPP_STRASSEN = ./strassen/main.cpp ./pthreads/pthreads.cpp ./strassen/strassen.cpp ./model/matrix.cpp ./io/input.cpp ./io/output.cpp

all: make_pthreads make_strassen clean

make_pthreads:
	$(CC) $(CFLAGS) -lm -lpthread -o $(BIN_PTHREADS) $(CPP_PTHREADS)

make_strassen:
	$(CC) $(CFLAGS) -lm -lpthread -o $(BIN_STRASSEN) $(CPP_STRASSEN)

include $(wildcard *.d)

clean:
	rm -f ./*/*.d
