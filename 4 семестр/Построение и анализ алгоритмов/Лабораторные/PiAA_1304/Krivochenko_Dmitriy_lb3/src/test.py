import random
import os
import shutil
import algorithm
import time

def show_progress(current_iteration, overall_amount):

    print("\033c", end='')
    print(f"Processed: {current_iteration}\{overall_amount}")

def rand_with_exclude(start, stop, excluded_num = 0):
    randInt = excluded_num
    while randInt == excluded_num:
        randInt = random.randint(start, stop)
    return randInt

def generate_rand_arr(start, stop, size):
    randArr = []
    for _ in range(size):
        randArr.append(rand_with_exclude(start, stop))
    return randArr

def generate_rand_matrix(start, stop, size):
    matrix = [generate_rand_arr(start, stop, size) for _ in range(size)]
    for i in range(size):
        matrix[i][i] = -1
    return matrix

def matrix_to_string(matrix):
    return '\n'.join([' '.join([str(c) for c in lst]) for lst in matrix])


def write_matrix_to_file(matrix, filename, file_destination):
    f = open(file_destination + '\\' + filename, 'a+')
    f.write(matrix_to_string(matrix))
    f.close()



def generate_test_files(amount, matrSize = 20):
    cur_path = os.path.abspath(os.getcwd())
    dir_name = '\\file_chamber'
    folder_path = cur_path + dir_name
    if os.path.isdir(folder_path):
        shutil.rmtree(folder_path)
    os.makedirs(folder_path)
    for i in range(amount):
        write_matrix_to_file(generate_rand_matrix(-1, 100, matrSize), f'test_matr_{i}.txt', folder_path)
    


def start_testing(amount):
    generate_test_files(amount)
    cur_path = os.path.abspath(os.getcwd())
    folder_path = cur_path + '\\file_chamber'
    time_list = []
    testing_result = ""
    for i in range(amount):
        test_matr_path = folder_path + f'\\test_matr_{i}.txt'
        start_time = time.time()
        path, cost = algorithm.solve(test_matr_path)
        end_time = time.time() - start_time
        time_list.append(end_time)
        testing_result += f"Iteration: {i + 1}\n{path}, {cost}, {end_time}s\n"
        show_progress(i+1, amount)
    testing_result = f'Average time: {round(sum(time_list)/len(time_list), 2)}s\n' + testing_result
    with open("test_output.txt", "w+") as f:
        f.write(testing_result)
    return testing_result

start_testing(5)
