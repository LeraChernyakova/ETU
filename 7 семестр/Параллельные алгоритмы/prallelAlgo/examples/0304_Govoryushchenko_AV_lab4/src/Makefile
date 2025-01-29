CXX = g++
CXXFLAGS = -g3
COMMON_SOURCES = matrix.cpp

all: main

main: main.o $(patsubst .cpp,.o,$(COMMON_SOURCES))
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f main
