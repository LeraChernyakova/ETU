#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <vector>

#include <thread>
#include <chrono>

using namespace std;


void generate_matrix(const std::string& filename, int rows, int columns){
    ofstream file;
    file.open(filename);
    if (!file){
        cout << "Can't open file generate matrix\n";
        return;
    }
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            file << rand() % 100 << ' ';
        }
        file << std::endl;
    }
    file.close();
}

void read_matrix(vector<vector<int>>& matrix, string filename){
    ifstream file(filename);
    if (!file){
        cout << "Can't open file read matrix";
        return;
    }

    string line;
    string delimiter = " ";
    vector<int> row;


    while (getline(file, line)){
        row.clear();
        size_t pos;

        while ((pos = line.find(delimiter)) != std::string::npos) {
            row.push_back(stoi(line.substr(0, pos)));
            line.erase(0, pos + delimiter.length());
        }
        matrix.push_back(row);
    }

    file.close();
}

void read_matrices(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2){
    read_matrix(matrix1, "/home/master/work/etu/PA/lab1/matrix_1.txt");
    read_matrix(matrix2, "/home/master/work/etu/PA/lab1/matrix_2.txt");
}

void multiply_matrices(vector<vector<int>>& matrix1, vector<vector<int>>& matrix2, vector<vector<int>>& matrix_res, int start, int end){
    int row1 = matrix1.size();
    int col1 = matrix1[0].size();
    int row2 = matrix2.size();
    int col2 = matrix2[0].size();



    for(int i = start; i <= end; i++){
        for(int j = 0; j < col2; j++){
            for(int k = 0; k < col1; k++)
                matrix_res[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }
}

void write_result(vector<vector<int>> matrix_res, string filename){
    ofstream file;
    file.open("/home/master/work/etu/PA/lab1/" + filename);
    for (int i = 0; i < matrix_res.size(); i++){
        for(int j = 0; j < matrix_res[i].size(); j++){
            file << matrix_res[i][j] << ' ';
        }
        file << std::endl;
    }
    file.close();
}

int main(){
    generate_matrix("/home/master/work/etu/PA/lab1/matrix_1.txt", 1000, 1000);
    generate_matrix("/home/master/work/etu/PA/lab1/matrix_2.txt", 1000, 1000);

    vector<vector<int>> matrix1;
    vector<vector<int>> matrix2;
    int num_threads = 1;

    auto start_time = chrono::high_resolution_clock::now();

    thread thread_read(read_matrices, std::ref(matrix1), std::ref(matrix2));
    thread_read.join();

    vector<vector<int>> matrix_res(matrix1.size(), vector<int>(matrix2[0].size(), 0));


    vector<thread> thread_vec;
    int min_num_rows_thread = matrix1.size() / num_threads;
    int max_num_rows_thread = min_num_rows_thread + 1;
    int num_threads_with_max_rows = matrix1.size() % num_threads;

    for (int i = 0; i < num_threads; i++){
        if (i < num_threads_with_max_rows)
            thread_vec.push_back(thread(multiply_matrices, ref(matrix1), ref(matrix2), ref(matrix_res),
            i * max_num_rows_thread, (i + 1) * max_num_rows_thread));
        else
            thread_vec.push_back(thread(multiply_matrices, ref(matrix1), ref(matrix2), ref(matrix_res),
            num_threads_with_max_rows * max_num_rows_thread + (i - num_threads_with_max_rows) * min_num_rows_thread,
            num_threads_with_max_rows * max_num_rows_thread + (i - num_threads_with_max_rows + 1) * min_num_rows_thread - 1));

    }

    for (int i = 0; i < thread_vec.size(); i++)
        thread_vec[i].join();

    thread threat_write(write_result, ref(matrix_res), "pthreads_res.txt");
    threat_write.join();

    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time);

    cout << "Duration " << num_threads << " threads: "<< duration.count() << " ms" << endl;


}
