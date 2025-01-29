CXXFLAGS = -g
INCLUDES = . ../common
SOURCES  = socket \
		 unix_socket \
		 common \
		 ../common/matrix \
		 ../common/matrix_slice \
		 ../common/utils

all: in_proc calc_proc out_proc thread_proc thread_proc_par

in_proc: in_proc.o $(addsuffix .o,$(SOURCES))
	$(CXX) $(CXXFLAGS) -pthread -o $@ $^

calc_proc: calc_proc.o $(addsuffix .o,$(SOURCES))
	$(CXX) $(CXXFLAGS) -pthread -o $@ $^

out_proc: out_proc.o $(addsuffix .o,$(SOURCES))
	$(CXX) $(CXXFLAGS) -pthread -o $@ $^

thread_proc: thread_proc.o thread_sync.o $(addsuffix .o,$(SOURCES))
	$(CXX) $(CXXFLAGS) -pthread -o $@ $^

thread_proc_par: thread_proc_par.o thread_sync.o $(addsuffix .o,$(SOURCES))
	$(CXX) $(CXXFLAGS) -pthread -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCLUDES)) -c $< -o $@


.PHONY: clean

clean:
	rm -f *.o
	rm -f in_proc calc_proc out_proc thread_proc thread_proc_par
