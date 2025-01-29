#include "matrix_reader/matrix_reader.hpp"
#include "result_writer/result_writer.hpp"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <cmath>
#include <iostream>

void* get_shared_memory(){
    int id = shmget(1, 4194304, 0644 | IPC_CREAT);
    void* pointer = shmat(id, nullptr, 0);
    return pointer;
}

int* write_to_shared_memory(int* shared_memory, std::vector<std::vector<int>> matrix) {
    int height = matrix.size();
    int width = matrix[0].size();
    *shared_memory = height;
    shared_memory++;
    *shared_memory = width;
    shared_memory++;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            *shared_memory = matrix[i][j];
            shared_memory++;
        }
    }
    return shared_memory;
}

std::vector<std::vector<int>> read_from_shared_memory(int* shared_memory) {
    int height = *shared_memory;
    shared_memory++;
    int width = *shared_memory;
    shared_memory++;
    std::vector<std::vector<int>> matrix(height, std::vector<int>(width));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            matrix[i][j] = *shared_memory;
            shared_memory++;
        }
    }
    return matrix;
}

void read_process() {
    std::vector<std::vector<int>> first_multiplier = read_first_multiplier();
    std::vector<std::vector<int>> second_multiplier = read_second_multiplier();
    int* shared_memory = (int*)get_shared_memory();
    shared_memory = write_to_shared_memory(shared_memory, first_multiplier);
    write_to_shared_memory(shared_memory, second_multiplier);
}

void multiplication_process() {
    int* shared_memory = (int*)get_shared_memory();
    std::vector<std::vector<int>> first_multiplier = read_from_shared_memory(shared_memory);
    shared_memory += (2 + first_multiplier.size() * first_multiplier[0].size());
    std::vector<std::vector<int>> second_multiplier = read_from_shared_memory(shared_memory);
    shared_memory -= (2 + first_multiplier.size() * first_multiplier[0].size());
    int height = first_multiplier.size();
    int width = second_multiplier[0].size();
    int equal_line = second_multiplier.size();
    std::vector<std::vector<int>> result_matrix(height, std::vector<int>(width));
    int tmp_sum;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tmp_sum = 0;
            for (int n = 0; n < equal_line; n++) {
                tmp_sum += (first_multiplier[i][n] * second_multiplier[n][j]);
            }
            result_matrix[i][j] = tmp_sum;
        }
    }
    write_to_shared_memory(shared_memory, result_matrix);
}

void write_process() {
    int* shared_memory = (int*)get_shared_memory();
    std::vector<std::vector<int>> result_matrix = read_from_shared_memory(shared_memory);
    write_result(result_matrix);
}


int main() {

    pid_t read_pid = fork();
    switch(read_pid){
        case 0:
            read_process();
            exit(0);
        default:
            wait(&read_pid); 
    }
    
    pid_t multiplication_pid = fork();
    switch(multiplication_pid){
        case 0:
            multiplication_process();
            exit(0);
        default:
            wait(&multiplication_pid); 
    }

    pid_t write_pid = fork();
    switch(write_pid){
        case 0:
            write_process();
            exit(0);
        default:
            wait(&write_pid); 
    }

    return 0;
}