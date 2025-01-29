output: output/main.o output/processes_stage_sep.o output/threads_stage_sep.o output/threads_multiply.o output/matrix.o
	g++ output/main.o output/processes_stage_sep.o output/threads_stage_sep.o output/threads_multiply.o output/matrix.o -o output/output.out

output/main.o: main.cpp
	g++ -c main.cpp -o output/main.o

output/processes_stage_sep.o: tasks/processes_stage_sep.cpp tasks/tasks.h
	g++ -c tasks/processes_stage_sep.cpp -o output/processes_stage_sep.o

output/threads_stage_sep.o: tasks/threads_stage_sep.cpp tasks/tasks.h
	g++ -c tasks/threads_stage_sep.cpp -o output/threads_stage_sep.o

output/threads_multiply.o: tasks/threads_multiply.cpp tasks/tasks.h
	g++ -c tasks/threads_multiply.cpp -o output/threads_multiply.o

output/matrix.o: utils/matrix.cpp utils/matrix.h
	g++ -c utils/matrix.cpp -o output/matrix.o

clean: 
	rm output/*

run:
	output/output.out