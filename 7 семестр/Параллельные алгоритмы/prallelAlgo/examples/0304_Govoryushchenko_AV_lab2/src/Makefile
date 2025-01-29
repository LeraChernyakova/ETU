CXX = g++
CXXFLAGS = -g3
COMMON_SOURCES = matrix.cpp common.cpp

all: pThreadProg

pThreadProg: pThreadProg.o $(patsubst .cpp,.o,$(COMMON_SOURCES))
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f pThreadProg
