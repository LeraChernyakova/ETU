CC = g++
CFLAGS = -g -Wall -MMD -D_REENTRANT

BIN_PROCESSES = ./bin/processes.exe
BIN_THREADS = ./bin/threads.exe
BIN_PTHREADS = ./bin/pthreads.exe
BIN_RESEARCH = ./bin/research.exe

CPP_PROCESSES = ./processes/main.cpp ./processes/sharedMemory.cpp ./model/matrix.cpp ./io/input.cpp ./io/output.cpp
CPP_THREADS = ./threads/main.cpp ./model/matrix.cpp ./io/input.cpp ./io/output.cpp
CPP_PTHREADS = ./pthreads/main.cpp ./model/matrix.cpp ./io/input.cpp ./io/output.cpp
CPP_RESEARCH = ./pthreads/research.cpp ./model/matrix.cpp ./io/input.cpp ./io/output.cpp

all: make_processes make_threads make_pthreads clean

processes: make_processes clean

threads: make_threads clean

pthreads: make_pthreads clean

research: make_research clean

make_processes:
	$(CC) $(CFLAGS) -lm -lpthread -o $(BIN_PROCESSES) $(CPP_PROCESSES)

make_threads:
	$(CC) $(CFLAGS) -lm -lpthread -o $(BIN_THREADS) $(CPP_THREADS)

make_pthreads:
	$(CC) $(CFLAGS) -lm -lpthread -o $(BIN_PTHREADS) $(CPP_PTHREADS)

make_research:
	$(CC) $(CFLAGS) -lm -lpthread -o $(BIN_RESEARCH) $(CPP_RESEARCH)

include $(wildcard *.d)

clean:
	rm -f ./bin/*.o ./bin/*.d
