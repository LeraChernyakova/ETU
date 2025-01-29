CC = g++
CFLAGS = -g -Wall -MMD -D_REENTRANT

BIN_LOCKFREE = ./bin/main.exe

CPP_LOCKFREE = ./lockfree/main.cpp ./model/matrix.cpp ./io/input.cpp ./io/output.cpp ./lockfree/LockFreeQueue.cpp

all: make_lockfree clean

make_lockfree:
	$(CC) $(CFLAGS) -lm -lpthread -o $(BIN_LOCKFREE) $(CPP_LOCKFREE)

include $(wildcard *.d)

clean:
	rm -f ./*/*.d
