CC = g++
CFLAGS = -g -Wall -MMD -D_REENTRANT

BIN_ROUGH = ./bin/main_rough.exe
BIN_THIN = ./bin/main_thin.exe

CPP_ROUGH = ./rough/main.cpp ./model/matrix.cpp ./io/input.cpp ./io/output.cpp
CPP_THIN = ./thin/main.cpp ./model/matrix.cpp ./io/input.cpp ./io/output.cpp ./thin/ThinQueue.cpp

all: make_rough make_thin clean

make_rough:
	$(CC) $(CFLAGS) -lm -lpthread -o $(BIN_ROUGH) $(CPP_ROUGH)

make_thin:
	$(CC) $(CFLAGS) -lm -lpthread -o $(BIN_THIN) $(CPP_THIN)

include $(wildcard *.d)

clean:
	rm -f ./*/*.d
