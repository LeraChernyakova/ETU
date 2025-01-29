#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>

#include "matrix_operations.h"

using namespace std;

int main(){
    int n = 0, m = 0;
    int id_mult, id_write;
    cout<<"Введите размер матриц: ";
    cin>>m>>n;
    vector<vector<int>> first_matrix(m, vector<int>(n));
    vector<vector<int>> second_matrix(n, vector<int>(m));
    vector<vector<int>> result_matrix(m, vector<int>(m));

    generate_matrix(first_matrix, m, n);
    generate_matrix(second_matrix, n, m);
    
    id_mult = fork();
    switch(id_mult){
        case -1:
            exit(-1);
        case 0:
            result_matrix = multiply_matrices(first_matrix, second_matrix, m, n);
            id_write = fork();
            switch (id_write){
                case -1:
                    exit(-1);
                case 0:
                    print_res(result_matrix, m);
                    exit(0);
                default:
                    wait(&id_write);
            }
            exit(0);
        default:
            wait(&id_mult);
    }
    return 0;
}