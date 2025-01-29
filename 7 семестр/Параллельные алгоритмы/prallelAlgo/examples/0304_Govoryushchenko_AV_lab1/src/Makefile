CXX = g++
CXXFLAGS = -g3
COMMON_SOURCES = matrix.cpp common.cpp socket.cpp serverSocket.cpp

all: reader writer executor threadProg pThreadProg

reader: reader.o $(patsubst .cpp,.o,$(COMMON_SOURCES))
	$(CXX) $(CXXFLAGS) $^ -o $@

writer: writer.o $(patsubst .cpp,.o,$(COMMON_SOURCES))
	$(CXX) $(CXXFLAGS) $^ -o $@

executor: executor.o $(patsubst .cpp,.o,$(COMMON_SOURCES))
	$(CXX) $(CXXFLAGS) $^ -o $@

threadProg: threadProg.o $(patsubst .cpp,.o,$(COMMON_SOURCES))
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread

pThreadProg: pThreadProg.o $(patsubst .cpp,.o,$(COMMON_SOURCES))
	$(CXX) $(CXXFLAGS) $^ -o $@ -pthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f reader writer executor threadProg pThreadProg
